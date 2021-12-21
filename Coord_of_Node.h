class Coord_of_Node{
  private:
    double x;
    double y;
    double z;
  public:


    void setX(double x){
      this->x = x;
    }
    void setY(double y){
      this->y = y;
    }
    void setZ(double z){
      this->z = z;
    }

    const double getX(){
      return x;
    }
    const double getY(){
      return y;
    }
    const double getZ(){
      return z;
    }

    const std::string printCoordinate(){
      return ("x = " + std::to_string(x) + ", y = " + std::to_string(y) + ", z = " + std::to_string(z) );
    }

    Coord_of_Node(double x, double y, double z){
      setX(x);
      setY(y);
      setZ(z);
    }
};
