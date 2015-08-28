class Controls
{
  final static int LEFT_KEY = 0;
  final static int RIGHT_KEY = 1;
  final static int THRUST_KEY = 2;
  final static int SHOOT_KEY = 3;
  final static int RADIUS_DECREASE_KEY = 4;
  final static int RADIUS_INCREASE_KEY = 5;

  Player player;
  boolean[] keys;

  Controls(Player p)
  {
    player = p;
    keys = new boolean[6];

    for (int i = 0; i < keys.length; i++)
    {
      keys[i] = false;
    }
  }

  public void update()
  {
    if (keys[THRUST_KEY])
      player.accelerate();
    if (keys[LEFT_KEY])
      player.steer(false);
    if (keys[RIGHT_KEY])
      player.steer(true);
    if (keys[SHOOT_KEY])
      player.shoot();
    else
      player.stopShooting();
  }
}

void keyPressed()
{
  if (keyCode == LEFT)
    controls.keys[0] = true;
  if (keyCode == RIGHT)
    controls.keys[1] = true;
  if (keyCode == UP)
    controls.keys[2] = true;
  if (key == ' ')
    controls.keys[3] = true;
  if (key == 's')
  {
    //cp5.getProperties().getSnapshot("params");
    cp5.getProperties().save();
  }
  if (key == 'l')
  {
    cp5.getProperties().load();
    //cp5.getProperties().setSnapshot("params");
  }
}
void keyReleased()
{
  if (keyCode == LEFT)
    controls.keys[0] = false;
  if (keyCode == RIGHT)
    controls.keys[1] = false;
  if (keyCode == UP)
    controls.keys[2] = false;
  if (key == ' ')
    controls.keys[3] = false;
  if (key == 'p')
    pause = !pause;
}

float getMouseX() {
  return mouseX - translateX;
}
float getMouseY() {
  return mouseY - translateY;
}

