/* Explode */
// Creates an "explosion" by finding all pixels near a point and launching them away
void explode(int xPos, int yPos, float radius) {
  float radiusSq = radius * radius;
  
  // loop through every x from xPos-radius to xPos+radius
  for (int x = xPos - (int)radius; x < xPos + (int)radius; x += terrain.destructionRes) {
    
    // first make sure that the x is within terrain's boundaries
    if (x > 0 && x < terrain.width()) { 
      
      // next loop through every y pos in this x column
      for (int y = yPos - (int)radius; y < yPos + (int)radius; y += terrain.destructionRes) {
        
        if (y > 0 && y < terrain.height()) { // boundary check
        
          // first determine if this pixel (or if any contained within its square area) is solid
          int solidX = 0,solidY = 0;
          boolean solid = false;
          // loop through every pixel from (xPos,yPos) to (xPos + destructionRes, yPos + destructionRes)
          // to find whether this area is solid or not
          for (int i = 0; i < terrain.destructionRes && !solid; i++) {
            for (int j = 0; j < terrain.destructionRes && !solid; j++) {
              int terrainTag = terrain.isPixelSolid(x+i,y+j);
              if (terrainTag == 1) {
                solid = true;
                solidX = x+i;
                solidY = y+j;
              }
            }
          }
          if (solid) { // we know this pixel is solid, now we need to find out if it's close enough
            float xDiff = x - xPos;
            float yDiff = y - yPos;
            float distSq = xDiff * xDiff + yDiff * yDiff;
            // if the distance squared is less than radius squared, then it's within the explosion radius
            if (distSq < radiusSq) {
              // finally calculate the distance
              //float distance = sqrt(distSq);
              
              // the speed will be based on how far the pixel is from the center
              //float speed = 800 * (1 - distance/radius);
              
              //if (distance == 0)
                //distance = 0.001; // prevent divide by zero in next two statements
                
              // velocity
              //float velX = speed * (xDiff + random(-10,10)) / distance; 
              //float velY = speed * (yDiff + random(-10,10)) / distance;
              
              // create the dynamic pixel
              //DynamicPixel pixel = new DynamicPixel(terrain.getColor(solidX, solidY), x,y, velX, velY, terrain.destructionRes);
              //pixel.stickiness = 800;
              //physics.add(pixel);
              //renderer.add(pixel);
              
              // remove the static pixels
              for (int i = 0; i < terrain.destructionRes; i++) {
                for (int j = 0; j < terrain.destructionRes; j++) {
                  terrain.removePixel(x+i,y+j);
                }
              }
            }
          }
        }
      }  
    }
  }
}
