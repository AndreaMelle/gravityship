/* PhysicsObj */
// Any object that will need motion integrated will implement this
// these methods allows the Physics class to forward the object's position using its velocity
abstract class PhysicsObj extends GameObj
{
  PhysicsObj(PVector p, PVector s, PVector a, float d)
  {
    position = p.get();
    speed = s.get();
    accel = a.get();
    drag = d;
    gravity = true;
  }

  PhysicsObj()
  {
    position = new PVector(0, 0);
    speed = new PVector(0, 0);
    accel = new PVector(0, 0);
    drag = 0;
    gravity = true;
  }

  public PVector position;
  public PVector speed;
  public PVector accel;
  public float drag; // 0.99 for the ship
  public boolean gravity;

  abstract void checkConstraints();
}


class Physics
{

  PVector gravity;
  PVector archimede;

  long previousTime;
  long currentTime;
  final int fixedDeltaTime = 16;
  float fixedDeltaTimeSeconds = (float)fixedDeltaTime / 1000.0;
  int leftOverDeltaTime = 0;

  ArrayList<PhysicsObj> objects;
  
  boolean isWater = false;

  // Constructor
  Physics() {
    objects = new ArrayList<PhysicsObj>();
    gravity = new PVector(0, 98.0); // will need tuning
    archimede = new PVector(0, -1000.0); // will need tuning
    gravity.mult(fixedDeltaTimeSeconds);
    archimede.mult(fixedDeltaTimeSeconds);
  }

  void add(PhysicsObj obj) {
    objects.add((int)random(objects.size()), obj);
  }
  void remove(PhysicsObj obj) {
    objects.remove(obj);
  }

  public void setGravity(float g)
  {
    gravity = new PVector(0, g); // will need tuning
    gravity.mult(fixedDeltaTimeSeconds);
  }

  // integrate motion
  void update() {
    // This game uses fixed-sized timesteps.
    // The amount of time elapsed since last update is split up into units of 16 ms
    // any left over is pushed over to the next update
    // we take those units of 16 ms and update the simulation that many times.
    // a fixed timestep will make collision detection and handling (in the Player class, esp.) a lot simpler
    // A low framerate will not compromise any collision detections, while it'll still run at a consistent speed. 

    currentTime = millis();
    long deltaTimeMS = currentTime - previousTime; // how much time has elapsed since the last update

      previousTime = currentTime; // reset previousTime

      // Find out how many timesteps we can fit inside the elapsed time
    int timeStepAmt = (int)((float)(deltaTimeMS + leftOverDeltaTime) / (float)fixedDeltaTime); 

    // Limit the timestep amount to prevent freezing
    timeStepAmt = min(timeStepAmt, 1);

    // store left over time for the next frame
    leftOverDeltaTime = (int)deltaTimeMS - (timeStepAmt * fixedDeltaTime);

    for (int iteration = 1; iteration <= timeStepAmt; iteration++) {
      for (int i = 0; i < objects.size (); i++) { // loop through every PhysicsObj

        PhysicsObj obj = objects.get(i);

        obj.accel.mult(fixedDeltaTimeSeconds);

        obj.speed.add(obj.accel);
        if (obj.gravity)
        {
          if (obj.position.y > 483 && obj.position.x < 250)
          {
            obj.speed.add(archimede);
          }
          
          obj.speed.add(gravity);
         
        }


        //if (obj.drag > 0 && obj.speed.mag() != 0)
        // {
        //obj.speed.mult(obj.drag); // decay speed (drag effect)
        //}

        obj.position.x = obj.position.x + obj.speed.x * fixedDeltaTimeSeconds;

        // if it's a player, only add y velocity if he's not on the ground.
        if (obj instanceof Player)
        {
          if (!(((Player)obj).onGround && obj.speed.y > 0))
          {
            obj.position.y = obj.position.y + obj.speed.y * fixedDeltaTimeSeconds;
          }
        } else
        {
          obj.position.y = obj.position.y + obj.speed.y * fixedDeltaTimeSeconds;
        }

        // allow the object to do collision detection and other things
        obj.checkConstraints();
      }
    }

    for (int i = 0; i < objects.size (); i++)
    {
      PhysicsObj obj = objects.get(i);
      obj.accel.set(0, 0);
    }
  }
}

