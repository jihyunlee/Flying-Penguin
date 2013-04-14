
class Surface {
  // We'll keep track of all of the surface points
  ArrayList<Vec2> surface;


  Surface() {
    surface = new ArrayList<Vec2>();
   
    // This is what box2d uses to put the surface in its world
    ChainShape chain = new ChainShape();

    surface.add(new Vec2(0,122));

    int startAngle = (int) degrees(PI*10/11);
    int endAngle = (int) degrees(PI*7/24);
    for(int a = startAngle-1; a >= endAngle; a--) {
      float x = 480 + 400 * cos(radians(a));
      float y = 0 + 400 * sin(radians(a));
      surface.add(new Vec2(x,y));
    }
    
    // Build an array of vertices in Box2D coordinates
    // from the ArrayList we made
    Vec2[] vertices = new Vec2[surface.size()];
    for (int i = 0; i < vertices.length; i++) {
      Vec2 edge = box2d.coordPixelsToWorld(surface.get(i));
      vertices[i] = edge;
    }
    
    // Create the chain!
    chain.createChain(vertices,vertices.length);
    
    // The edge chain is now attached to a body via a fixture
    BodyDef bd = new BodyDef();
    bd.position.set(0.0f,0.0f);
    Body body = box2d.createBody(bd);
    // Shortcut, we could define a fixture if we
    // want to specify frictions, restitution, etc.
    body.createFixture(chain,1);

  }

  // A simple function to just draw the edge chain as a series of vertex points
  void display() {
    strokeWeight(2);
    stroke(0);
    noFill();
    beginShape();
    for (Vec2 v: surface) {
      vertex(v.x,v.y);
    }
    endShape();
  }

}


