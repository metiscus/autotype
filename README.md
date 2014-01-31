autotype
========

### Intro
autotype is a tool for generating c++ classes from an xml file.

### Example

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
