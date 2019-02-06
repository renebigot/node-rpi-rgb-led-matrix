#include <v8.h>
#include <node.h>
#include <iostream>

#include <displayPrimitives.h>
using namespace v8; 
using namespace node; 

Point::Point (int x_, int y_) 
	: x(x_), y(y_)
{}

Line :: Line (const Point s, const Point e)
	: start(s), end(e)
{}

int Line :: yMax (void) const 
{
	return start.y > end.y ? start.y : end.y; 
}

int Line :: yMin (void) const 
{
	return start.y < end.y ? start.y : end.y; 
}

std::tuple<Point, bool>  Line :: intersection (const Line& l) const
{
	const auto null = std::make_tuple(Point(0, 0), false); 

	const int x1 = start.x; 
	const int y1 = start.y; 
	const int x2 = end.x; 
	const int y2 = end.y;

	const int x3 = l.start.x; 
	const int y3 = l.start.y; 
	const int x4 = l.end.x; 
	const int y4 = l.end.y; 

	//check if none of the lines are of length 0 
	if (( x1 == x2 && y1 == y2) || (x3 == x4 && y3 == y4)) return null; 
	
	//check if lines are parallel 
	const int denominator = ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	if (!denominator) return null; 

	const int ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denominator;
	const int ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denominator;

	if (ua < 0 || ua > 1 || ub < 0 || ub > 1) return null;

	const int x = x1 + ua * (x2 - x1);
	const int y = y1 + ua * (y2 - y1);

	return std::make_tuple( Point(x, y), true); 
}

Nan :: Persistent<v8::Function> SuperPolygon::constructor; 

SuperPolygon :: SuperPolygon (void)
{};

SuperPolygon :: ~SuperPolygon (void)
{};

void SuperPolygon :: New (const Nan::FunctionCallbackInfo<Value>& args)
{
	if (!args.IsConstructCall())
	{
		Nan::ThrowError("Super Polygon must be called as a constructor with 'new' keyword");
	}

	std::vector<int> x; 
	std::vector<int> y; 
	std::vector<Point> points; 

	Handle<Value> val;
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope handle_scope(isolate);

	if(args[0]->IsArray())
	{
		Handle<Array> jsArray = Handle<Array>::Cast(args[0]);
		for(unsigned int i = 0; i < jsArray->Length(); i++)
		{
			val = jsArray->Get(Integer::New(isolate, i));
			x.push_back(val->ToInteger()->Value());
		}
	}

	if(args[1]->IsArray())
	{
		Handle<Array> jsArray = Handle<Array>::Cast(args[1]);
		for(unsigned int i = 0; i < jsArray->Length(); i++)
		{
			val = jsArray->Get(Integer::New(isolate, i));
			y.push_back(val->ToInteger()->Value());
		}
	}

	if( (x.size() == y.size()) && x.size() > 0)
	{
		for(unsigned int i = 0; i < x.size(); i++)
		{
			points.push_back( Point(x[i], y[i]));
		}
	}
	else Nan::ThrowError("paramters must be two integer arrays of equal length");


	for(const auto p : points)
	{
		std::cout << p.x << ' ' << p.y << std::endl;
	}

	SuperPolygon* poly = new SuperPolygon(); 
	poly->Wrap(args.This());

	args.GetReturnValue().Set(args.This());
}


void SuperPolygon :: Init (v8::Local<v8::Object> exports)
{
	Nan::HandleScope scope; 

	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New); 

	tpl->SetClassName(Nan::New("SuperPolygon").ToLocalChecked()); 
	tpl->InstanceTemplate()->SetInternalFieldCount(1); 

	Nan::SetPrototypeMethod(tpl, "Draw", Draw); 
	
	constructor.Reset(tpl->GetFunction()); 

	exports->Set(Nan::New("SuperPolygon").ToLocalChecked(), tpl->GetFunction());
}

void SuperPolygon :: Draw (void)
{
	std::cout << "DRAW CALLED ON SUPER POLYGON" << std::endl;
}

void SuperPolygon :: Draw (const Nan::FunctionCallbackInfo<v8::Value>& args)
{
	SuperPolygon* poly = ObjectWrap::Unwrap<SuperPolygon>(args.Holder());

	poly->Draw();
}

