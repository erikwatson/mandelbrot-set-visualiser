#version 410 core

in vec2 TexCoords; // Input texture coordinates
out vec4 FragColor; // Output color

uniform float iTime;
uniform vec2 iResolution;

uniform float iZoom;
uniform vec2 iPosition;

// figure out where a value lies in a new coordinate space 
float scaleTo(float value, float oldMax, float oldMin, float newMax, float newMin) {   
    float oldRange = oldMax - oldMin;
    float newRange = newMax - newMin;
    
    return (((value - oldMin) * newRange) / oldRange) + newMin;
}

vec3 hsv2rgb(vec3 c) {
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 rgb2hsv(vec3 c) {
  vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
  vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
  vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

  float d = q.x - min(q.w, q.y);
  float e = 1.0e-10;

  return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

// Program
void mainImage(out vec4 fragColor, in vec2 fragCoord) {
  float zoom = iZoom;
  float zoomBase = 20.0;
  float maxZoom = zoomBase * zoomBase * zoomBase;
  
  const int maxIterations = 700;
  
  if(zoom < 0.3){
      zoom = 0.3;
  }
  
  if(zoom > maxZoom){
      zoom = maxZoom;
  }
  
  // Swap these comments out for other preset zooms 
  
  // vec2 offset = vec2(-1.5019 * zoom, 0.0 * zoom); // babybrot set 
  // vec2 offset = vec2(-0.74986 * zoom, 0.021 * zoom); // into the seahorse valley
  // vec2 offset = vec2(0.26031 * zoom, 0.00156 * zoom); // up the butt 
  // vec2 offset = vec2(0.3137846 * zoom, 0.0356986 * zoom); // in the eye 
  // vec2 offset = vec2(0.33532 * zoom, 0.400623 * zoom);
  // vec2 offset = vec2(0.4 * zoom, 0.0 * zoom);

  vec2 offset = vec2(iPosition.x * zoom, iPosition.y * zoom);
  
  // the Colour of this pixel 
  vec3 colour = vec3(0);
  
  // the position of this pixel in it's new space 
  vec2 position = vec2(scaleTo(fragCoord.x, iResolution.x, 0.0, (1.0 + offset.x) / zoom, (-2.5 + offset.x) / zoom),
                        scaleTo(fragCoord.y, iResolution.y, 0.0, (1.0 + offset.y) / zoom, (-1.0 + offset.y) / zoom));
  
  // plot the point
  int iterations = 0;
  
  vec2 z = position;
  bool escaped = false;
  
  float ca = -0.70176;
  float cb = -0.3842;
  
  for(int i = 0; i < maxIterations; i++) {
      
      // if the point is > 4 then it escapes the set, so drop it
      if((z.x * z.x) + (z.y * z.y) > (4.0)) {
          escaped = true;
          break;
      }
      
      // z = z^2 + c - this is where the magic happens 
      float newX = z.x * z.x - z.y * z.y + position.x;
      
      z.y = 2.0 * z.x * z.y + position.y;
      z.x = newX;
      
      iterations ++;
  }
  
  if(!escaped){
      colour = vec3(0.0);
  } else {
    float speed = 10.0;
    float t = iTime; // for some reason the colours "stack" rather than cycle, not sure why
    
    float tval = speed - (t - ((t / speed) ));
    
    float startPos = scaleTo(tval, speed, 0.0, 1.0, 0.0);
    
    colour = hsv2rgb(vec3(scaleTo(float(iterations), float(maxIterations), 1.0, 1.0, startPos),
                          scaleTo(float(iterations), float(maxIterations), 1.0, 1.0, 0.5), 
                          0.75));
  }
    
	fragColor = vec4(colour, 1.0); // set the pixel 
}

void main() {
  mainImage(FragColor, gl_FragCoord.xy);
}