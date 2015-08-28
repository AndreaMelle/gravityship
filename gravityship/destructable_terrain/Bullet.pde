/* Bullet */
// Acts similarly to PhysicsPixel
Bullet CreateBullet(PVector pos, PVector vel, float r)
{
  Bullet bullet = new Bullet(pos, vel, r);
  gameObjects.add(bullet);
  bullet.init();
  return bullet;
}

Bullet CreateBullet(PVector pos, PVector vel, float r, boolean _impactTerrain)
{
  Bullet bullet = new Bullet(pos, vel, r, _impactTerrain);
  gameObjects.add(bullet);
  bullet.init();
  return bullet;
}

class Bullet extends PhysicsObj implements RenderObj
{
  PVector last;
  float radius = 10;
  boolean impactTerrain = true; 

  Bullet(PVector pos, PVector vel, float r, boolean _impactTerrain ) {
    super(pos.get(), vel.get(), new PVector(0, 0), 0);
    impactTerrain = _impactTerrain;
    last = pos.get();
    radius = r;
  }

  Bullet(PVector pos, PVector vel, float r ) {
    super(pos.get(), vel.get(), new PVector(0, 0), 0);
    impactTerrain = true;
    last = pos.get();
    radius = r;
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

  public void checkConstraints()
  {

    if (this.markForDestroy)
      return;

    PVector seg_v = PVector.sub(position, last);
    PVector seg_v_unit = seg_v.get();
    seg_v_unit.normalize();
    PVector closest;
    PVector pt_v;
    float proj;

    for (int i = 0; i < enemies.size (); i++)
    {
      Enemy e = enemies.get(i);

      pt_v = PVector.sub(e.position, last);
      proj = PVector.dot(pt_v, seg_v_unit);

      if (proj <= 0)
        closest = last;
      else if ((proj * proj) >= seg_v.magSq())
        closest = position;
      else
      {
        closest = PVector.add(PVector.mult(seg_v_unit, proj), last);
      }

      if (PVector.sub(e.position, closest).magSq() < (e.radius * e.radius))
      {
        this.markForDestroy = true;
        e.markForDestroy = true;
        return;
      }
    }

    pt_v = PVector.sub(player.position, last);
    proj = PVector.dot(pt_v, seg_v_unit);

    if (proj <= 0)
      closest = last;
    else if ((proj * proj) >= seg_v.magSq())
      closest = position;
    else
    {
      closest = PVector.add(PVector.mult(seg_v_unit, proj), last);
    }

    if (PVector.sub(player.position, closest).magSq() < (player.playerRadius * player.playerRadius))
    {
      this.markForDestroy = true;
      player.markForDestroy = true;
      return;
    }

    int[] collision = rayCast((int)last.x, (int)last.y, (int)position.x, (int)position.y);

    if (collision.length > 0)
    {
      this.markForDestroy = true;
      if (impactTerrain)
        explode(collision[2], collision[3], radius);
      return;
    }

    last.x = position.x;
    last.y = position.y;
  }

  public void draw() {
    fill(0);
    rect(position.x, position.y, 3, 3);
  }
}

