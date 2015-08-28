
class Player extends PhysicsObj implements RenderObj
{
  public int deaths = 0;
  public float direction;
  public float force = 500;
  public float bulletForce = 250;
  public float steeringForce = 0.1;

  public color playerColor = color(255, 255, 255);

  // Are we shooting?
  boolean shooting;
  boolean shootingAlt;
  boolean isAccelerating;
  //boolean isDead = false;

  // last time (ms) a bullet was shot, used to limit the firing rate
  long lastShot;

  // variables for physics
  boolean onGround; // are we allowed to jump?
  boolean topBlocked;

  int playerRadius = 20;

  float bulletRadius = 10;

  PVector [] collisionSensors;
  PVector [] referenceCollisionSensors;

  float dx;
  float dy;

  // Constructor
  Player(int x, int y)
  {
    super(new PVector(x, y), new PVector(0, 0), new PVector(0, 0), 0.99);
    collisionSensors = new PVector[9];
    referenceCollisionSensors = new PVector[9];

    collisionSensors[0] = new PVector(0, 0);
    referenceCollisionSensors[0] = new PVector(0, 0);

    float angle = 0;

    for (int i = 1; i < collisionSensors.length; i++)
    {
      angle += radians(45.0);
      collisionSensors[i] = new PVector(playerRadius * sin(angle), -playerRadius * cos(angle));
      referenceCollisionSensors[i] = collisionSensors[i].get();
    }
    gravity = false;
  }

  public void init()
  {
    physics.add(this);
    renderer.add(this);
    super.init();
  }

  public void destroy()
  {
    super.destroy();
    renderer.remove(this);
    physics.remove(this);
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
    if (!shootingAlt)
      shooting = true;
  }

  public void stopShooting()
  {
    shooting = false;
  }

  public void shootAlt()
  {
    if (!shooting)
      shootingAlt = true;
  }

  public void stopShootingAlt()
  {
    shootingAlt = false;
  }

  public void draw()
  {
    pushMatrix();
    translate(position.x, position.y);
    rotate(direction);
    noStroke();
    fill(playerColor); 
    triangle(-10, 20, 10, 20, 0, -20);

    if (isAccelerating) {
      fill(255, 100, 100);
      triangle(-5, 22, 5, 22, 0, 40);
      isAccelerating = false;
    }

    popMatrix();

    // Debug drawing

    stroke(255, 150, 150);
    line(position.x + 5 * dx, position.y + 5 * dy, position.x + 10 * dx, position.y + 10 * dy);
    noFill();
    ellipse(position.x, position.y, playerRadius * 2, playerRadius * 2);
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

  public void respawn()
  {
    this.markForDestroy = false;
    direction = 0;
    position.set(100, 100);        
    speed.set(0, 0);
    accel.set(0, 0);
    shooting = false;
    deaths++;
  }

  public void update()
  {


    dx = sin(direction);
    dy = -cos(direction);

    for (int i = 0; i < collisionSensors.length; i++)
    {
      collisionSensors[i].set(referenceCollisionSensors[i].x, referenceCollisionSensors[i].y);
      collisionSensors[i].rotate(direction);
    }

    if (shooting || shootingAlt)
    {
      // Primary fire happens every 200 ms, alternate fire happens every 25 ms.
      if (!(shooting && millis() - lastShot < 150) && !(shootingAlt && millis() - lastShot < 15)) {
        if (shooting) {
          CreateBullet(new PVector(5 * dx + position.x + collisionSensors[8].x, 5 * dy + position.y + collisionSensors[8].y), new PVector(bulletForce * dx, bulletForce * dy), bulletRadius);
        } else {
          //          colorMode(HSB, 255); 
          //          for (int i = 0; i < 150; i++) { // create 150 particles
          //            DynamicPixel pixel = new DynamicPixel(color((int)(((millis()/5000f) * 255f) % 255), 255, 255), // color
          //            player.pos.x, player.pos.y, // position
          //            random(-50, 50) + random(1500, 2500) * diffX / len, random(-50, 50) + random(1500, 2500) * diffY / len, // speed
          //            terrain.destructionRes); // size
          //            physics.add(pixel);
          //            renderer.add(pixel);
          //          }
          //          colorMode(RGB, 255);
        }
        lastShot = millis();
      }
    }
  }

  public void checkConstraints()
  {
    if (this.markForDestroy)
      return;

    for (int i = 0; i < enemies.size(); i++)
    {
      Enemy e = enemies.get(i);
      float e_dx = e.position.x - position.x;
      float e_dy = e.position.y - position.y;
      float e_dist = e_dx * e_dx + e_dy * e_dy;

      if (e_dist < ((e.radius + playerRadius) * (e.radius + playerRadius)))
      {
        this.markForDestroy = true;
        e.markForDestroy = true;
      }
    }

    for (int i = 0; i < collisionSensors.length; i++)
    {
      int x = (int)(collisionSensors[i].x + position.x);
      int y = (int)(collisionSensors[i].y + position.y);

      if (terrain.isPixelSolid(x, y) > 0)
      {
        this.markForDestroy = true;
        break;
      }
    }

    // collision with pickups
    for (int i = 0; i < pickups.size (); i++) {
      Pickup p = pickups.get(i);

      float p_dx = p.position.x - position.x;
      float p_dy = p.position.y - position.y;
      float p_dist = p_dx * p_dx + p_dy * p_dy;

      if (p_dist < ((p.radius + playerRadius) * (p.radius + playerRadius)))
      {
        //p->applyToPlayer(this); //or something
        p.apply(this);
        p.markForDestroy = true;
      }
    }
  }
}

