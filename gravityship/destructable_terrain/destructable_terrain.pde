import java.util.Map;
import controlP5.*;

ControlP5 cp5;
Slider bulletSizeSlider, gravitySlider, thrustSlider, bulletForceSlider;
Terrain terrain;
PImage bg;

Physics physics; // has a list of all physics objects, and uses their velocity to move them
Renderer renderer; // has a list of all renderable objects, and calls their draw() method
Player player;
Controls controls;
ArrayList<Pickup> pickups;
ArrayList<Enemy> enemies;

// translation, used to keep track of where the camera is
int translateX;
int translateY;
boolean pause = false;

ArrayList<GameObj> gameObjects;

void setup()
{
  size(1136 / 2, 640 / 2, P3D);

  gameObjects = new ArrayList<GameObj>();

  cp5 = new ControlP5(this);

  // name, minValue, maxValue, defaultValue, x, y, width, height
  bulletSizeSlider = cp5.addSlider("bullet size", 1, 100, 10, 20, 40, 100, 14).addCallback(new CallbackListener()
  {
    public void controlEvent(CallbackEvent evt)
    {
      if (evt.getAction() == ControlP5.ACTION_BROADCAST) { 
        player.bulletRadius = bulletSizeSlider.getValue();
      }
    }
  }
  );

  bulletSizeSlider.getCaptionLabel().setColor(color(0, 102, 153));

  gravitySlider = cp5.addSlider("gravity", 1, 250, 98, 20, 60, 100, 14).addCallback(new CallbackListener()
  {
    public void controlEvent(CallbackEvent evt)
    {
      if (evt.getAction() == ControlP5.ACTION_BROADCAST) { 
        physics.setGravity(gravitySlider.getValue());
      }
    }
  }
  );

  gravitySlider.getCaptionLabel().setColor(color(0, 102, 153));

  thrustSlider = cp5.addSlider("thrust", 1, 1000, 500, 20, 80, 100, 14).addCallback(new CallbackListener()
  {
    public void controlEvent(CallbackEvent evt)
    {
      if (evt.getAction() == ControlP5.ACTION_BROADCAST) { 
        player.force = thrustSlider.getValue();
      }
    }
  }
  );

  thrustSlider.getCaptionLabel().setColor(color(0, 102, 153));

  bulletForceSlider = cp5.addSlider("bullet force", 1, 1000, 250, 20, 100, 100, 14).addCallback(new CallbackListener()
  {
    public void controlEvent(CallbackEvent evt)
    {
      if (evt.getAction() == ControlP5.ACTION_BROADCAST) { 
        player.bulletForce = bulletForceSlider.getValue();
      }
    }
  }
  );

  bulletForceSlider.getCaptionLabel().setColor(color(0, 102, 153));

  bg = loadImage("bg/sky-blurry.png");
  terrain = new Terrain(loadImage("maps/physics.png"), 1);

  // initialize the physics and rendering engines
  physics = new Physics();
  renderer = new Renderer();

  // create the player
  player = new Player(100, 100);
  controls = new Controls(player);
  gameObjects.add(player);

  pickups = new ArrayList<Pickup>();
  enemies = new ArrayList<Enemy>();

  Enemy e0 = new Enemy(300, 100);

  for (int i = 0; i < 10; i++)
  {
    Pickup p0 = new Pickup(500 + i * 80, (int)(200 + 40 * ((i % 2) - 0.5) ));
    gameObjects.add(p0);
    p0.init();
  }

  player.init();
  gameObjects.add(e0);
  e0.init();


  smooth(8);
  frameRate(60);
}

// Draw loop
void draw() {
  background(0);

  if (!pause)
  {
    controls.update();

    for (int i = 0; i < gameObjects.size (); i++) {
      gameObjects.get(i).update();
    }

    physics.update();
    terrain.update();
    translateX = (int)constrain(width/2 - player.position.x, width - terrain.width(), 0);
    translateY = (int)constrain(height/2 - player.position.y, height - terrain.height(), 0);

    // deletion loop

    for (int i = 0; i < gameObjects.size (); i++) {
      GameObj obj = gameObjects.get(i);
      if (obj.markForDestroy)
      {
        if (obj instanceof Player)
        {
          ((Player)obj).respawn();
        } else
        {
          obj.destroy();
          gameObjects.remove(obj);
        }
      }
    }
  }

  /* Rendering */
  // first move our perspective to where the player is
  pushMatrix();
  translate(translateX, translateY);
  image(bg, translateX * -0.8, translateY * -0.8);
  terrain.draw(0, 0);
  rectMode(CORNERS);
  fill(100,100,250);
  rect(0,483,250,696);
  rectMode(CORNER);
  //showNormals();
  renderer.draw();
  popMatrix();

  fill(0, 102, 153);
  text("deaths: " + player.deaths, 20, 20);
}

abstract class GameObj
{
  public boolean markForDestroy = false;
  public boolean isInited = false;

  public void init()
  {
    markForDestroy = false;
    isInited = true;
  }

  public void update() {
  }

  public void destroy()
  {
    if (!markForDestroy)
      return;

    markForDestroy = false;
    isInited = false;
  }
}

