class NotInImage{};
class Image {
public:
  int w,h;
  double*dat;
  Image(int w,int h):w(w),h(h){
    dat=new double[w*h];
  }
  double&operator()(int i,int j){
    return dat[i+w*j];
  }
  double operator()(double x,double y){
    if(x<0||x>=w||y<0||y>=h)
      throw NotInImage();
    int
      i=(int)x,
      j=(int)y;
    double
      a=(*this)(i,j),
      b=(*this)(i+1,j),
      c=(*this)(i+1,j+1),
      d=(*this)(i,j+1),
      rx=x-i,
      rx1=1-rx,
      ab=b*rx+a*rx1,
      dc=c*rx+d*rx1,
      ry=y-j;
    return dc*ry+ab*(1-ry);
  }
};

#define doall(img,cmds) \
do{ \
  const double sfx=1./(img).w,sfy=1./(img).h; \
  for(int j=0;j<(img).h;j++){ \
    double y=(j-(img).h/2)*sfy; \
    for(int i=0;i<(img).w;i++){ \
      double x=(i-(img).w/2)*sfx; \
      cmds; \
    } \
  } \
}while(0)

#include <iostream>
#include <math.h>
using namespace std;

int
main()
{
  Image rr(128,128);
  doall(rr,rr(i,j)=hypot(i-rr.w/2,j-rr.h/2));
  for(double d=0;d<80;d+=3.8)
    cout << d << " " << rr(d,d/2) << endl;
  return 0;
}
