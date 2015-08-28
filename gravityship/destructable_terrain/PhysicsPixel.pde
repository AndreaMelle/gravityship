/* Dynamic Pixel */
// Pixels in motion
//class DynamicPixel implements PhysicsObj, RenderObj {
//  float x,y; // location
//  float lastX, lastY; // last location, used for our "ray casting"
//  
//  float velX, velY;
//  
//  float stickiness = 1500; // minimum speed for this pixel to stick
//  float bounceFriction = 0.85; // scalar multiplied to velocity after bouncing
//  
//  color col; // color of the pixel
// 
//  int size = 1; // width and height of the pixel
//  
//  DynamicPixel(color c, float x, float y, float vX, float vY, int size) {
//    col = c;
//    this.x = x; this.y = y;
//    lastX = x; lastY = y;
//    velX = vX; velY = vY;
//    
//    this.size = size;
//  }
//  
//  // Render the pixel (method implemented as a RenderObj)
//  public void draw() {
//    fill(col);
//    noStroke();
//    rect(x,y, size, size);
//  }
//  
//  // Methods implemented as a PhysicsObj
//  float getX() { return x; }
//  float getY() { return y; }
//  float getVX() { return velX; }
//  float getVY() { return velY; }
//  void setX(float pX) { x = pX; }
//  void setY(float pY) { y = pY; }
//  void setVX(float vX) { velX = vX; }
//  void setVY(float vY) { velY = vY; }
//  
//  // CheckConstraints, also implemented as a PhysicsObj
//  public void checkConstraints() {
//    // Find if there's a collision between the current and last points
//    int[] collision = rayCast((int)lastX, (int)lastY, (int)x, (int)y);
//    if (collision.length > 0) 
//      collide(collision[0], collision[1], collision[2], collision[3]);
//      
//    // reset last positions
//    lastX = x;
//    lastY = y;
//    
//    // Boundary constraints... only remove the pixel if it exits the sides or bottom of the map
//    if (x > terrain.width() || x < 0 || y > terrain.height()) {
//      renderer.remove(this);
//      physics.remove(this);
//    }
//  }
//  
//  /* Collide */
//  // called whenever checkConstraints() detects a solid pixel in the way
//  void collide(int thisX, int thisY, int thatX, int thatY) {
//    // first determine if we should stick or if we should bounce
//    if (velX * velX + velY * velY < stickiness * stickiness) { // if the velocity's length is less than our stickiness property, add the pixel
//      // draw a rectangle by looping from x to size, and from y to size
//      for (int i = 0; i < size; i++) { 
//        for (int j = 0; j < size; j++) {
//          terrain.addPixel(col, thisX+i, thisY+j);
//        }  
//      }
//      // remove this dynamic pixel
//      renderer.remove(this);
//      physics.remove(this);
//    }
//    else { // otherwise, bounce
//      // find the normal at the collision point
//      
//      // to do this, we need to reflect the velocity across the edge normal at the collision point
//      // this is done using a 2D vector reflection formula ( http://en.wikipedia.org/wiki/Reflection_(mathematics) )
//      
//      float pixelNormal[] = terrain.getNormal((int)thatX, (int)thatY);
//      
//      float d = 2 * (velX * pixelNormal[0] + velY * pixelNormal[1]);
//      
//      velX -= pixelNormal[0] * d;
//      velY -= pixelNormal[1] * d;
//      
//      // apply bounce friction
//      velX *= bounceFriction;
//      velY *= bounceFriction;
//      
//      // reset x and y so that the pixel starts at point of collision
//      x = thisX;
//      y = thisY;
//    }
//  }
//}
