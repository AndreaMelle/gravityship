
// Anything we want drawn should implement this
interface RenderObj {
  void draw();  
}
/* Renderer */
// Holds a list of all "RenderObj"s, anything with a draw() method.
class Renderer {
  
  ArrayList<RenderObj> objects;
  
  Renderer() {
    objects = new ArrayList<RenderObj>(); 
  }  
  
  void draw() {
    for (RenderObj obj : objects) 
      obj.draw();
  }
  
  void add(RenderObj obj) {
    objects.add(0, obj);
  }
  void remove(RenderObj obj) {
    objects.remove(obj); 
  }
}

void showNormals() {
  stroke(0);
  // Scan the terrain in a gridlike pattern, and only draw normals at pixels that have a range of solid pixels surrounding them
  for (int x = 0; x < terrain.width(); x += 10) {
    for (int y = 0; y < terrain.height(); y += 10) {
      int solidCount = 0;
      // scan solid pixels around this pixel
      for (int i = -5; i <= 5; i++) {
        for (int j = -5; j <= 5; j++) {
          if (terrain.isPixelSolid(x+i,y+j) > 0) {
            solidCount++;
          }
        }
      }
      // if there's too many solid pixels, then it's probably underground, and not a surface
      // if there's not enough solid pixels, then it's probably in the air, and not a surface
      if (solidCount < 110 && solidCount > 30) {
        float[] pixelNormal = terrain.getNormal(x,y);
        if (pixelNormal.length > 0 && !Float.isNaN(pixelNormal[0]) && !Float.isNaN(pixelNormal[1]))
          line(x,y, x + 10 * pixelNormal[0], y + 10 * pixelNormal[1]);
      }
    }
  }
}
