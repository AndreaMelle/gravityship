/* Terrain */
// Provides methods for determining solid/empty pixels, and for removing/adding solid pixels 
class Terrain {
  PImage img; // the terrain image
  
  int destructionRes; // how wide is a static pixel
  
  // Constructor
  Terrain(PImage pic, int destructionRes) {
    this.destructionRes = destructionRes;
    
    // Copy pic over to img, replacing all pink (RGB: 255,0,255) pixels with transparent pixels
    img = createImage(pic.width, pic.height, ARGB);
    img.loadPixels();
    pic.loadPixels();
    for (int i = 0; i < img.width * img.height; i++) {
      if (red(pic.pixels[i]) == 255 && green(pic.pixels[i]) == 0 && blue(pic.pixels[i]) == 255) 
        img.pixels[i] = color(0,0);
      else
        img.pixels[i] = pic.pixels[i];
    }
    img.updatePixels();
  } 
  
  // Render terrain onto the main screen
  void draw(float x, float y) {
    image(img, x,y);  
  }
  
  // Return the terrain's width and height
  public int width() {
    return img.width;  
  }
  public int height() {
    return img.height; 
  }
  
  // Update - apply pixels[]'s changes onto the image
  void update() {
    img.updatePixels(); 
  }
  
  // Determine if a pixel is solid based on whether or not it's transparent
  int isPixelSolid(int x, int y) {
    if (x > 0 && x < img.width && y > 0 && y < img.height)
    {
      color c = img.pixels[x + y * img.width];
      if(red(c) == 255 && green(c) == 0 && blue(c) == 0)
      {
        return 2;
      }
      else if(red(c) == 0 && green(c) == 255 && blue(c) == 0)
      {
        return 1;
      }
      else return 0;
    }
    return 0; // border is not solid
  }
  
  // Color in a pixel, making it solid
  void addPixel(color c, int x, int y) {
    if (x > 0 && x < img.width && y > 0 && y < img.height)
      img.pixels[x + y * img.width] = c;
  }
  // Make a pixel solid
  void removePixel(int x, int y) {
    if (x > 0 && x < img.width && y > 0 && y < img.height)
      img.pixels[x + y * img.width] = color(0,0);
  }
  // Get a pixel's color
  color getColor(int x, int y) {
    if (x > 0 && x < img.width && y > 0 && y < img.height)
      return img.pixels[x + y * img.width];
    return 0;
  }
  
  // Find a normal at a position
  float[] getNormal(int x, int y) {
    // First find all nearby solid pixels, and create a vector to the average solid pixel from (x,y)
    float avgX = 0;
    float avgY = 0;
    for (int w = -3; w <= 3; w++) {
      for (int h = -3; h <= 3; h++) {
        if (isPixelSolid(x + w, y + h) > 0) {
          avgX -= w;
          avgY -= h;
        }
      }
    }
    float len = sqrt(avgX * avgX + avgY * avgY); // get the distance from (x,y)
    return new float[]{avgX/len, avgY/len}; // normalize the vector by dividing by that distance
  }
}
