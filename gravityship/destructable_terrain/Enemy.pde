class Enemy extends PhysicsObj implements RenderObj
{
  public float direction;
  public float force = 500;
  public float bulletForce = 250;
  public float steeringForce = 0.025;

  boolean shooting = true;
  boolean isAccelerating;
  long lastShot;
  int radius = 20;
  float bulletRadius = 10;

  PVector [] collisionSensors;
  PVector [] referenceCollisionSensors;

  float dx;
  float dy;

  PImage img;

  Enemy(int x, int y)
  {
    super(new PVector(x, y), new PVector(0, 0), new PVector(0, 0), 0.99);

    PImage temp = loadImage("enemy01.png");
    img = createImage(temp.width, temp.height, ARGB);
    img.loadPixels();
    temp.loadPixels();
    for (int i = 0; i < img.width * img.height; i++) {
      if (red(temp.pixels[i]) == 255 && green(temp.pixels[i]) == 0 && blue(temp.pixels[i]) == 255) 
        img.pixels[i] = color(0, 0);
      else
        img.pixels[i] = temp.pixels[i];
    }
    img.updatePixels();



    collisionSensors = new PVector[9];
    referenceCollisionSensors = new PVector[9];

    collisionSensors[0] = new PVector(0, 0);
    referenceCollisionSensors[0] = new PVector(0, 0);

    float angle = 0;

    for (int i = 1; i < collisionSensors.length; i++)
    {
      angle += radians(45.0);
      collisionSensors[i] = new PVector(radius * sin(angle), -radius * cos(angle));
      referenceCollisionSensors[i] = collisionSensors[i].get();
    }

    gravity = false;
  }

  public void init()
  {
    physics.add(this);
    renderer.add(this);
    enemies.add(this);
    super.init();
  }

  public void destroy()
  {
    super.destroy();
    renderer.remove(this);
    physics.remove(this);
    enemies.remove(this);
  }

  public void setBulletRadius(float r)
  {
    bulletRadius = r;
  }

  public float getBulletRadius()
  {
    return bulletRadius;
  }

  public void accelerate()
  {
    this.accel.x = force * sin(direction);
    this.accel.y = -force * cos(direction);
    isAccelerating = true;
  }

  public void steer(boolean right)
  {
    direction = right ? (direction + steeringForce) : (direction - steeringForce);
  }

  public void shoot()
  {
    shooting = true;
  }

  public void stopShooting()
  {
    shooting = false;
  }

  public void draw()
  {
    pushMatrix();
    translate(position.x, position.y);
    rotate(direction);
    image(img, -img.width / 2, -img.height / 2);
    popMatrix();

    // Debug drawing

    stroke(255, 150, 150);
    line(position.x + 5 * dx, position.y + 5 * dy, position.x + 10 * dx, position.y + 10 * dy);
    noFill();
    ellipse(position.x, position.y, radius * 2, radius * 2);
    noStroke();

    fill(255, 0, 0);
    for (int i = 0; i < collisionSensors.length; i++)
    {
      if (i == 4)
        fill(0, 0, 255);
      else if (i == 8)
        fill(0, 255, 0);
      else
        fill(255, 0, 0);

      rect(position.x + collisionSensors[i].x, position.y + collisionSensors[i].y, 3, 3);
    }
  }

  //  public void respawn()
  //  {
  //    this.markForDestroy = false;
  //    direction = 0;
  //    position.set(100, 100);        
  //    speed.set(0, 0);
  //    accel.set(0, 0);
  //    shooting = false;
  //    deaths++;
  //  }

  public void update()
  {
    steer(true);

    dx = sin(direction);
    dy = -cos(direction);

    for (int i = 0; i < collisionSensors.length; i++)
    {
      collisionSensors[i].set(referenceCollisionSensors[i].x, referenceCollisionSensors[i].y);
      collisionSensors[i].rotate(direction);
    }

    if (shooting)
    {
      if (!(shooting && millis() - lastShot < 500))
      {
        // we add some margin otherwise we are shooting ourselves
        if (shooting)
          CreateBullet(new PVector(position.x + collisionSensors[8].x + 5 * dx, 5 * dy + position.y + collisionSensors[8].y), new PVector(bulletForce * dx, bulletForce * dy), bulletRadius, false);
        lastShot = millis();
      }
    }
  }

  public void checkConstraints()
  {
    if (this.markForDestroy)
      return;

    


    //    for (int i = 0; i < collisionSensors.length; i++)
    //    {
    //      int x = (int)(collisionSensors[i].x + position.x);
    //      int y = (int)(collisionSensors[i].y + position.y);
    //
    //      if (terrain.isPixelSolid(x, y) > 0)
    //      {
    //        this.markForDestroy = true;
    //        break;
    //      }
    //    }
  }
}

