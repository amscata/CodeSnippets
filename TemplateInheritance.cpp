// Example program
#include <iostream>
#include <string>

template <typename T>
class BaseCreator
{
public:
    template<typename U, typename... Args>
	T* create(U first, Args... args);
	
	void destroy(T* obj)
	{
	    delete obj;
	}
};

template <typename T>
class DerivedCreator : public BaseCreator<T>
{
public:
    template<typename U, typename... Args>
	T* create(U first, Args... args)
	{
		return new T(first, args...);
	}
};

class Pos3D
{
public:
    Pos3D(double x, double y) : m_x(x), m_y(y), m_z(0)
    {
    }
    
    Pos3D(double x, double y, double z) : m_x(x), m_y(y), m_z(z)
    {
    }

    double m_x;
    double m_y;
    double m_z;
};

std::ostream& operator<<(std::ostream& stream, const Pos3D& pos3d)
{
    stream << "[" << pos3d.m_x << ", " << pos3d.m_y << ", " << pos3d.m_z << "]";
    return stream;
}

int main()
{	
	DerivedCreator<Pos3D> creator;
	auto pos1 = creator.create(2, 3);
	auto pos2 = creator.create(2, 3, 4);
	std::cout << *pos1 << std::endl;
	std::cout << *pos2 << std::endl;
	creator.destroy(pos1);
	creator.destroy(pos2);
}
