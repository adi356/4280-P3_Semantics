xdata x1 : 1
x2 : 2
x3 : 3 ;
xopen
  xout << x2 ;
  xin >> x1 ;
  xlet x1 x3 + x1 ;
  { xdata x4 : 1
x5 : 2 ;
    xout << x4 / x5 + x1 ;
  }
  xout << x3 ;
xclose