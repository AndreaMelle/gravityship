//extends PhysicsObj
class Pickup extends GameObj implements RenderObj
{
  public int radius = 20;
  public PVector position;
  color pickupColor;

  //PVector [] collisionSensors;
  //PVector [] referenceCollisionSensors;

  // Constructor
  Pickup(int x, int y)
  {
    position = new PVector(x, y);
    pickupColor = color(random(255),random(255),random(255));
    //collisionSensors = new PVector[9];
    //referenceCollisionSensors = new PVector[9];

    //collisionSensors[0] = new PVector(0, 0);
    //referenceCollisionSensors[0] = new PVector(0, 0);

    //    float angle = 0;
    //
    //    for (int i = 1; i < collisionSensors.length; i++)
    //    {
    //      angle += radians(45.0);
    //      collisionSensors[i] = new PVector(playerRadius * sin(angle), -playerRadius * cos(angle));
    //      referenceCollisionSensors[i] = collisionSensors[i].get();
    //    }
  }

  public void init()
  {
    pickups.add(this);
    renderer.add(this);
    super.init();
  }

  public void destroy()
  {
    super.destroy();
    renderer.remove(this);
    pickups.remove(this);
  }

  public void apply(Player p)
  {
    p.playerColor = pickupColor;
  }

  public void draw()
  {
    pushMatrix();
    translate(position.x, position.y);

    stroke(255, 150, 150);
    noFill();
    ellipse(0, 0, radius * 2, radius * 2);
    noStroke();

    fill(pickupColor);
    noStroke();
    ellipse(0, 0, radius, radius);

    popMatrix();    

    //    fill(255, 0, 0);
    //    for (int i = 0; i < collisionSensors.length; i++)
    //    {
    //      if (i == 4)
    //        fill(0, 0, 255);
    //      else if (i == 8)
    //        fill(0, 255, 0);
    //      else
    //        fill(255, 0, 0);
    //
    //      rect(position.x + collisionSensors[i].x, position.y + collisionSensors[i].y, 3, 3);
    //    }
  }
}

