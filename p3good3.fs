xdata x1 : 1
x2 : 2
x3 : 3 ;
xopen
  xout << 1 ;
  xin >> x1 ;
  xlet x1 22 ;
  { xdata x4 : 1
    x5 : 2 ;
    xout << x6 + x4 ;
    { xdata x6 : 1
x7 : 2 ;
      xout << x7 - x2 ;
    }
}
  xout << 1 ;
xclose