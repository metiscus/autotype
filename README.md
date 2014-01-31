autotype
========

### Intro
autotype is a tool for generating c++ classes from an xml file.

### Input Example

```xml
<typecc version='1.0'>

  <class name='user'>
    <member name='Id' type='int' />
    <member name='Username' type='String' />
    <member name='Password' type='String' />
    <member name='Salt' type='String' />
    <member name='Email' type='String' />
  </class>
   
  <typedef name='UserList' type='user*' listType='list' />

  <enum name='MovementDirection'>
    <enum_value name='MOVE_UP' />
    <enum_value name='MOVE_DOWN' />
    <enum_value name='MOVE_LEFT' />
    <enum_value name='MOVE_RIGHT' />
  </enum>
  
  <class name='location'>
    <member name='Id' type='int' />
    <member name='X' type='int' />
    <member name='Y' type='int' />
    <member name='Direction' type='MovementDirection' />
  </class>
  
</typecc>  
```

### Output Example
```c++
#pragma once
#include <map>
#include <string>
#include <list>
#include <vector>

typedef std::string String;

class user{
private:
	int		mId;
	String		mUsername;
	String		mPassword;
	String		mSalt;
	String		mEmail;

public:
	int& GetId( ) { return mId; }
	const int& GetId( ) const { return mId; }
	void SetId(const int& in ) { mId = in; }
	String& GetUsername( ) { return mUsername; }
	const String& GetUsername( ) const { return mUsername; }
	void SetUsername(const String& in ) { mUsername = in; }
	String& GetPassword( ) { return mPassword; }
	const String& GetPassword( ) const { return mPassword; }
	void SetPassword(const String& in ) { mPassword = in; }
	String& GetSalt( ) { return mSalt; }
	const String& GetSalt( ) const { return mSalt; }
	void SetSalt(const String& in ) { mSalt = in; }
	String& GetEmail( ) { return mEmail; }
	const String& GetEmail( ) const { return mEmail; }
	void SetEmail(const String& in ) { mEmail = in; }
};

typedef std::list<user*> UserList;
enum MovementDirection{
	MOVE_UP = 0,
	MOVE_DOWN = 1,
	MOVE_LEFT = 2,
	MOVE_RIGHT = 3,
};

class location{
private:
	int		mId;
	int		mX;
	int		mY;
	MovementDirection		mDirection;
	float		mMultiplier;
	int		mBonus;
	int		mBridgeTo;

public:
	int& GetId( ) { return mId; }
	const int& GetId( ) const { return mId; }
	void SetId(const int& in ) { mId = in; }
	int& GetX( ) { return mX; }
	const int& GetX( ) const { return mX; }
	void SetX(const int& in ) { mX = in; }
	int& GetY( ) { return mY; }
	const int& GetY( ) const { return mY; }
	void SetY(const int& in ) { mY = in; }
	MovementDirection& GetDirection( ) { return mDirection; }
	const MovementDirection& GetDirection( ) const { return mDirection; }
	void SetDirection(const MovementDirection& in ) { mDirection = in; }
};
```
