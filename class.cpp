#include <iostream>
#include <cmath>
#include <vector>

#define PI 3.14159265

class tdvector{
	public:
		tdvector();
		tdvector(double x, double y, double z);
		~tdvector();
		tdvector& operator = (tdvector src);
		tdvector(const tdvector & other);
		tdvector operator + (const tdvector & other);  //vector + vector
		tdvector operator - (const tdvector & other);  // vector - vector	
		double  operator * (tdvector  & other);  // dot product vector vector return type integer
		tdvector operator / (const tdvector & other);  // cross product vector vector return vector
		tdvector operator & (double a);  // scaler multiplication
		tdvector giveunitvector(); // gives unit vector
		double getmag();
		void display();
	private:
		std::vector <double> vect;
		double mag = 0;
	friend class vp;
};

tdvector::tdvector () // no argument constructor, nil constructor
{
	vect.resize(3);
} 
tdvector::~tdvector(){} //destructor
tdvector::tdvector (double x, double y=0, double z=0)  // constructor
{	
	vect.resize(3);
	vect[0] = x;
	vect[1] = y;
	vect[2] = z;
	auto sum = 0;
	for(auto itvect: vect)
	{
		sum += std::pow(itvect, 2);
	}
	mag = std::sqrt(sum);
}
tdvector::tdvector(const tdvector & other) //copy constructor
{
	vect = other.vect;
	mag = other.mag;
}
tdvector& tdvector::operator = (tdvector src) // copy assignment // copy and swap idiom
{
	std::swap(vect, src.vect);
	std::swap(mag, src.mag);
	return *this;
}
tdvector tdvector::operator + (const tdvector & other)
{	
	tdvector result(vect[0] + other.vect[0], vect[1] + other.vect[1], vect[2] + other.vect[2]);
	return result;	
}
tdvector tdvector::operator - (const tdvector & other)
{	
	tdvector result(vect[0] - other.vect[0], vect[1] - other.vect[1], vect[2] - other.vect[2]);
	return result;	
}
tdvector tdvector::operator & (double a)
{
	tdvector result(vect[0]* a , vect[1] * a, vect[2] * a);
	return result;
}
double tdvector:: operator * (tdvector & other)
{
	tdvector a = *this; // operator overloader
	tdvector b = other;
	auto x = a.vect[0] * b.vect[0] +  a.vect[1] * b.vect[1] +  a.vect[2] * b.vect[2] ;
        return x;	
}
void tdvector::display()
{
	std::cout << vect[0] << "i" << " + " << vect[1] << "j" << " + " << vect[2] << "k" << std::endl;
}
tdvector tdvector::giveunitvector()
{	
	tdvector result(vect[0]/mag, vect[1]/mag, vect[2]/mag);
	return result;
}
double tdvector::getmag()
{
	return mag;
}
tdvector tdvector:: operator / (const tdvector& other)
{
	tdvector result((vect[1]*other.vect[2]-vect[2]*other.vect[1]) , -1*(vect[0]*other.vect[2]-vect[2]*other.vect[0]), (vect[0]*other.vect[1]-vect[1]*other.vect[0]));
	return result;
}
class vp
{
	public:
		vp();
		double boxproduct(tdvector a, tdvector b, tdvector c);//volume of the parallelopiped formed by these vectors (a/b)*c
		tdvector tripleproduct(tdvector a, tdvector b, tdvector c); // a / (b/c) info:- a / (b/c) != (a/b)/c
		double areaoftriangle(tdvector a, tdvector b, tdvector c); // area of the triangle with position vectors
		double vot(tdvector a, tdvector b, tdvector c, tdvector d);  // volume of tetrahedron with position vectors
		bool areCoplaner(tdvector a, tdvector b, tdvector c, tdvector d); //checks for coplanarity of vectors position vectors
		bool areColinear(tdvector a, tdvector b, tdvector c); // check colinerity position vectors
		std::vector <tdvector>  component(tdvector a, tdvector b, tdvector c, tdvector r);
		double anglebetween(tdvector a, tdvector b);

};
vp::vp(){}
double vp::boxproduct(tdvector a, tdvector b, tdvector c)  
{
	tdvector j = b/c;
	auto g = a * j;
	return g; 
}
double vp::vot(tdvector a, tdvector b, tdvector c, tdvector d)  // volume of a terahedrom with one vertex as its origin
{	
	auto x = a - d;
	auto y = b - d;
	auto z = c - d;
	return boxproduct(x,y,z) / 6 ;
}
bool vp::areCoplaner(tdvector a, tdvector b, tdvector c, tdvector d)  // to check if the given 3 vectors are coplaner
{
	auto x = a - d;
	auto y = b - d;
	auto z = c - d;
	return boxproduct(x,y,z) == 0 ? 1 : 0; // if volume == 0 then coplaner
}
double vp::areaoftriangle(tdvector a, tdvector b, tdvector c)
{
	auto a1 = a - b;
	auto a2 = a - c;
	auto b1 = a1 / a2;     // area = magnitude[(0.5) (a-b / a-c)]   
	return b1.getmag() / 2;
}
bool vp::areColinear(tdvector a, tdvector b, tdvector c)
{
	return areaoftriangle(a,b,c) == 0 ? 1 : 0;  // if area == 0 then colinear
}

tdvector vp::tripleproduct(tdvector a, tdvector b, tdvector c)
{
	tdvector f = b / c;
	tdvector m = a / f;
	return m;
}
std::vector <tdvector>  vp::component(tdvector a, tdvector b, tdvector c, tdvector r)
{
	a = a.giveunitvector();
	auto num1 = r * a;
	auto a1 = a & num1;
	b = b.giveunitvector();
	auto num2 = r * b;
	auto b1 = b & num2;
	c = c.giveunitvector();
	auto num3 = r * c;
	auto c1 = c & num3;
	std::vector <tdvector> result;
	result.push_back(a1);
	result.push_back(b1);
	result.push_back(c1);
	return result;
}
double vp::anglebetween(tdvector a, tdvector b)
{
	auto x = a.giveunitvector();
	auto y = b.giveunitvector();
	auto p = x * y;
	auto result = std::acos (p) * 180.0 / PI;
	return result;
}
int main()
{	
	tdvector l(4,0,0);
	tdvector kl(4,3,0);
	tdvector hd(1,4,2);
	tdvector jkl;
	tdvector p(2);
	tdvector h(0,2);
	tdvector qa(0,0,2);
	tdvector r(2,2,2);
	auto addresult = l + hd;
	std::cout << "l, hd, add result "; addresult.display(); 
	auto dotresult = l * hd;
	std::cout << "l, hd, dot result " << dotresult << std::endl;
	auto crossresult = l / kl;
	std::cout << "l, kl, cross result "; crossresult.display();
	auto scalerresult = l & 10;
	std::cout << "l, 10, scaler result "; scalerresult.display();
	auto unitvectorresult = kl.giveunitvector();
	std::cout << "kl's unit vector "; unitvectorresult.display();

	vp mavic;
	auto boxproductresult = mavic.boxproduct(p,h,qa);
	std::cout << "p, h, qa box result " << boxproductresult << std::endl;
	auto tripleproductresult = mavic.tripleproduct(l, kl, hd);
	std::cout << "l, kl, hd triple product result "; tripleproductresult.display();
	int areaoftriangleresult = mavic.areaoftriangle(l,kl,jkl); // right angle triangle
	std::cout << "l, kl,jkl triangle area result " << areaoftriangleresult << std::endl;
	auto areCoplanerresult = mavic.areCoplaner(l,kl,jkl,p); // they lie in x-y plane
	std::cout << "l, kl, jkl, p areCoplaner result " << areCoplanerresult << std::endl;
	auto areColinearresult = mavic.areColinear(l,kl,jkl); // are not colinear form a triangle
	std::cout << "l, kl, jkl areColinear result " << areColinearresult << std::endl;
	auto anglebetweenresult = mavic.anglebetween(l,kl);
	std::cout << "l, kl anglebetween result " << anglebetweenresult << std::endl;

	auto res = mavic.component(p,h,qa,r);

	for(auto s:res){
	s.display();	
	}
}
