using System;
using System.Runtime.CompilerServices;

class Hello {
  [MethodImplAttribute(MethodImplOptions.InternalCall)]
  extern static string Sample();
}
