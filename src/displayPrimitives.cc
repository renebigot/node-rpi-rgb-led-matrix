#include <v8.h>
#include <node.h>
#include <iostream>

#include <displayPrimitives.h>
using namespace v8; 
using namespace node; 

Nan::Persistent<v8::Function> SuperPolygon::constructor; 

SuperPolygon::SuperPolygon (void)
{};

void SuperPolygon::New (const Nan::FunctionCallbackInfo<Value>& args)
{
	if (!args.IsConstructCall())
	{
		Nan::ThrowError("Super Polygon must be called as a constructor with 'new' keyword");
	}

	SuperPolygon* poly = new SuperPolygon(); 
	poly->Wrap(args.This());

	args.GetReturnValue().Set(args.This());
}


void SuperPolygon::Init (v8::Local<v8::Object> exports)
{
	Nan::HandleScope scope; 

	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New); 

	tpl->SetClassName(Nan::New("SuperPolygon").ToLocalChecked()); 
	tpl->InstanceTemplate()->SetInternalFieldCount(1); 

	Nan::SetPrototypeMethod(tpl, "Draw", Draw); 
	
	constructor.Reset(tpl->GetFunction()); 

	exports->Set(Nan::New("SuperPolygon").ToLocalChecked(), tpl->GetFunction());
}

void SuperPolygon::Draw (void)
{
	std::cout << "DRAW CALLED ON SUPER POLYGON" << std::endl;
}

void SuperPolygon::Draw (const Nan::FunctionCallbackInfo<v8::Value>& args)
{
	SuperPolygon* poly = ObjectWrap::Unwrap<SuperPolygon>(args.Holder());

	poly->Draw();
}
