#include <node.h>
#include <node_object_wrap.h>
#include <nan.h>

#include <vector>
#include <tuple> 

/*
struct Point 
{
	const int x; 
	const int y; 
	
	Point(int x_, int y_);
};

struct Line 
{
	const Point start;
	const Point end; 

	Line (const Point s, const Point e);
	int yMax (void) const; 
	int yMin (void) const; 
	bool intersects (const Line&) const; 
	Point intersection (const Line&) const; 
};
*/

class SuperPolygon : public node::ObjectWrap
{
	public:
	static Nan::Persistent<v8::Function> constructor; 
	static void Init(v8::Local<v8::Object> exports);
	static void New (const Nan::FunctionCallbackInfo<v8::Value>& args);

	void Draw (void); 

	protected:
	SuperPolygon (void);
	static void Draw (const Nan::FunctionCallbackInfo<v8::Value>&);

	/*
	void Draw (void); 
	void Fill (void);

	protected: 
	SuperPolygon ( const std::vector<Point>&); 
	virtual ~SuperPolygon (void); 

	static void Draw (const Nan::FunctionCallbackInfo<v8::Value>&); 
	static void Fill (const Nan::FunctionCallbackInfo<v8::Value>&);

	private: 
	std::tuple<int, int, int> boundryIntersections (const Line&);
	std::tuple<Point, Point>  clipBounds (void); 
	*/
};
