
<!---EQ LATEX 2 SVG EDITOR:  http://www.codecogs.com/latex/eqneditor.php -->
<!--- rawgit:   https://rawgit.com/   https://www.jsdelivr.com/rawgit   -->
<!--- template: https://www.tablesgenerator.com/#   --->
<!--- template: https://www.overleaf.com/learn/latex/Inserting_Images   --->
<!--- <br> <img  src="https:/   .svg?sanitize=true" alt="Alterantive_description"> <br> --->
<!--  somewhat nice intro text. http://www.docs.is.ed.ac.uk/skills/documents/3722/3722-2014.pdf -->
<!--- other nice intro text. https://www.latex-tutorial.com/tutorials/ -->

Failure rate

```latex
\lambda_{hour}   = \frac{r}{D \cdot H \cdot A_f} = \frac{r}{EDH}
\\
\\
\textup{where r is the number of failures or rejects }
```

<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/failure_rate_eq.svg?sanitize=true" alt="EDH equation"> <br>

Equivalent Device Hours:

```latex
EDH  = D \cdot H \cdot A_f
\\
\\
\textup{where: }
\\ 
\\ 
\begin{matrix}
 \mathbf{EDH}   & \textup{ Equivalent Device Hours } \\
 \mathbf{D}   & \textup{ Number of devices tested } \\
 \mathbf{H}   & \textup{ Test Hours per Device } \\
 \mathbf{A_f} & \textup{ Acceleration Factor derived from the Arrhenius equation }
\end{matrix}
```

<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/EDH_eq.svg?sanitize=true" alt="EDH equation"> <br>

Arrhenius equation:

```latex
A_f = e^{\frac{E_a}{k} ( \frac{1}{T_{use}} -  \frac{1}{T_{test}}) }
\\
\\
\textup{where: }
\\ 
\\ \: \:  \mathbf{E_a} \: \:  \textup{ Activation energy (eV) of the failure mode }
\\ \: \:  \mathbf{k} \: \:  \textup{ Boltzmann's Constant) = 8.617 x 10-5 eV/°K }
\\ \: \:  \mathbf{T_{use}} \: \:  \textup{ Use Temperature (standardized at 55°C or 328°K) }
\\ \: \:  \mathbf{T_{use}} \: \:  \textup{ Test Temperature (HTOL- High Temperature Operating Life temperature in °K) } 
\\ \: \:  \mathbf{ºK} \: \:  \textup{ (degrees Kelvin) = 273 + °C } 
\\ \: \:  \mathbf{eV} \: \:  \textup{ electron volts } 
```

<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/Arrhenius_eq.svg?sanitize=true" alt="Arrhenius equation"> <br>


Atmospheric equation:

the lagrange derivative of the velocity of the wind is:

```latex
\underset{acceleration}{\underbrace{ \rho \frac{DU}{Dt} } } =
\underset{Pressure \:  gradient}{\underbrace{- \triangledown P }}
+ \underset{gravity}{\underbrace{\rho g} }
+ \underset{friction}{\underbrace{\rho F_r}}
```

<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/atmospheric_eq.svg?sanitize=true" alt="atmospheric equation"> <br>


where:


```latex
\underset{acceleration}{\underbrace{ \rho \frac{D\mathbf{U}}{Dt} } } = 
\frac{\partial \mathbf{U}}{\partial t} + \mathbf{U} \cdot  \triangledown \boldsymbol{U}
```

<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/atmospheric_eq2.svg?sanitize=true" alt="atmospheric equation"> <br>


Pressure barometric law:

```latex
\\
\rho g A\, dz = ( P(z) + P(z+dz) ) \cdot  A  \\
\\
\frac{ ( P(z) + P(z+dz) )}{dz} = - \rho g
\\
\\
\frac{dP}{dz} = - \rho g
\\
\\
\rho = \frac{P M }{R T}
\\
\\
\frac{dP}{P} = - \frac{M g}{R T} dz
\\
\\
\ln P(z) - \ln P(0) = - \frac{M g}{R T} z
\\
\\
P(z) = P(0) \exp{- \frac{M g}{R T} z}
\\
\\
\textup{  so if we define a barometric height as: }
\\
\\
H = \frac{R T}{M g}
\\
\\
\textup{  then the barometric law is: }
\\
\\
P(z) = P(0) \exp{- \frac{z}{H}}
```


<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/barometric_law.svg?sanitize=true" alt="pressure barometric law equation"> <br>


Stress Equation

```latex
S  = \frac{F }{ A_0}
```
<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/StressEq.svg?sanitize=true" alt="engineering stress equation"> <br>

Engineering Strain

```latex
 \varepsilon _0 = \frac{L - L_0 }{ L_0}
``` 
<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/StrainEq.svg?sanitize=true" alt="engineering strain equation"> <br>

Hook's Law

```latex
 \sigma   = E \cdot  \varepsilon _0 
```
<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/HookLaw.svg?sanitize=true" alt="hook law equation"> <br>

Young modulus

```latex
 \sigma = E \cdot  \varepsilon _0 
\\
\\ & \textrm{}{E: modulus of Elasticity or Young modulus}
```
<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/YoungModulus.svg?sanitize=true" alt="Youngs modulous equation"> <br>


Bernouilli equation

```latex
P_1 + \frac{1}{2} \rho v_1^2 + \rho g h_1 = P_2 + \frac{1}{2} \rho v_2^2 + \rho g h_2
```

<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/Bernouilli_equation.svg?sanitize=true" alt="Bernouilli equation"> <br>

Aerodinamic drag force

```latex
 \textup{Aerodynamc Drag Force}= \frac{1}{2} \, \rho\,  C_x \,  v^2 
```

<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/aerodynamic_drag_force.svg?sanitize=true" alt="aerodynamic drag force"> <br>

Power in a fluid stream (as for wind turbines)

```latex
P = \frac{1}{2}   A V^3 C_f
\\
\left\{\begin{matrix}
\\ \varphi  & \textup{ - the fluid density}
\\  A   & \textup{  - the area of the stream of interest}
\\  V   & \textup{  - the velocity of the stream}
\\  C   &\textup{  - the efficiency coefficient}
\end{matrix}\right.
```

<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/powerinastream.svg?sanitize=true" alt="power in a fluid stream"> <br>


Golden ratio - Seccion Aurea

```latex
\frac{a+b}{a} = \frac{a}{b} = \phi 
```

<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/secci%C3%B3n_aurea_01.svg?sanitize=true" alt="golden ratio 1"> <br>


```latex
1 + \frac{1}{\phi } = \phi
```

<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/secci%C3%B3n_aurea_02.svg?sanitize=true" alt="golden ratio 1"> <br>


Sigmoid function

```latex
f(x) =  \frac{1}{1 + e^{-x}}
```

<br> <img  src="https://cdn.jsdelivr.net/gh/sergiocollado/potpourri/image/sigmoid.svg?sanitize=true" alt="sigmoid function"> <br> 

BAYES THEOREM

```latex
P(A|B)= \frac{P(B|A) \cdot P(A)}{P(B)}
```

<br> <img  src="https://cdn.jsdelivr.net/gh/sergiocollado/potpourri/image/Bayes.svg?sanitize=true" alt="Bayes theorem equation"> <br>

SNELL EQUATION

 <br> <img  src="https://cdn.jsdelivr.net/gh/sergiocollado/potpourri/image/snell_eq.svg?sanitize=true" alt="snell equation"> <br> 


```latex
\frac{\sin\theta_{1} }{\sin\theta_2} = \frac{ n_1 }{ n_2 }
```


CLASSICAL ROCKET EQUATION:

```latex
\Delta \nu  = \nu_e \ln \frac{ m_0}{ m_f}
```

<br> <img  src="https://rawgit.com/sergiocollado/potpourri/master/image/roquet_equation.svg?sanitize=true" alt="classical_rocket_equation"> <br>

```latex
\left\{\begin{matrix}\Delta \nu \: \: \: - & \:  \textrm{change of velocity}
\\  \nu_e \: \: \: -& \: \textrm{effective exhaust velocity}
\\  m_0 \: \: \: -& \: \textrm{initial total mass, included the fuel}
\\ m_f \: \: \: -& \: \textrm{final total mass}
\end{matrix}\right.
```
<br> <img  src="https://github.com/sergiocollado/potpourri/blob/master/image/leyenda_rocket_eq2.png" alt="classical_rocket_equation_parameters"> <br>

<br>
<br>

SCALAR COULOMB FORCE EQUATION

```latex
F = k_e \cdot \frac{Q_1 \cdot Q_2}{r^2}
```

<br> <img  src="https://rawgit.com/sergiocollado/potpourri/master/image/escalar_coulomb_force_eq.svg?sanitize=true" alt="escalar coulomb equation"> <br>

RACIONALIZATION OF COULOMB FORCE

```latex
\begin{align*}
F  &= k_e \cdot \frac{Q_1 \cdot Q_2}{r^2} 
\\ &= \frac{1}{4 \cdot \pi \cdot \varepsilon } \cdot \frac{Q_1 \cdot Q_2}{r^2}
\\ &= \frac{1}{4 \cdot \pi \cdot \varepsilon_r \cdot \varepsilon_0 } \cdot \frac{Q_1 \cdot Q_2}{r^2}
\\ &=\frac{1}{4\cdot\pi\cdot\varepsilon_r\cdot\frac{10^{-9}}{36\cdot\pi}}\cdot\frac{Q_1\cdot Q_2}{r^2}
\\ &= \frac{9 \cdot 10^{9}}{ \varepsilon_r } \cdot \frac{Q_1 \cdot Q_2}{r^2}
\end{align*}
```

RACIONALICED EQUATION OF COULOMB FORCE

```latex
F  =   \frac{9 \cdot 10^{9}}{ \varepsilon_r } \cdot \frac{Q_1 \cdot Q_2}{r^2}
```

ELECTROSTATIC FIELD

```latex
\overrightarrow{E} =  \frac{\overrightarrow{F}}{ q }
```


```latex
\overrightarrow{F}= q \cdot  \overrightarrow{E}
```



POSITION UNITARY VECTOR

```latex
\hat{r} = \frac{\vec{r}}{ \mid \vec{r}\mid }
```

A VECTOR:

```latex
\vec{A} = A_x \cdot \vec{i} + A_y \cdot \vec{j} + A_z \cdot \vec{k}
```
<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/A_vector.svg?sanitize=true" alt="A vector">
<br>


B VECTOR:

```latex
\vec{B} = B_x \cdot \vec{i} + B_y \cdot \vec{j} + B_z \cdot \vec{k}
```
<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/B_vector.svg?sanitize=true" alt="B vector">
<br>

DOT  PRODUCT:

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/Dot_product.svg?sanitize=true" alt="B vector">
<br>

```latex
\vec{A} \cdot \vec{B} = A_x \cdot B_x + A_y \cdot B_y + A_z \cdot B_z
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/Dot_product.2svg.svg?sanitize=true" alt="B vector">
<br>

```latex
\vec{A} \bullet  \vec{B} = \left |\vec{A}  \right | \cdot \left |  \vec{B}  \right | \cdot \cos (\hat{AB})
```


SIN THEOREM:

```latex
2·R = \frac{a}{\sin(A)} = \frac{b}{\sin(B)} = \frac{c}{\sin(C)}
```

COS THEOREM:

```latex
c^{2} = a^{2} + b^{2} - 2·a·b·\cos (C)
```

TAN THEOREM

```latex
\frac{a - b}{a + b} = \frac{ \tan{ \left( \frac{1}{2} (A-B) \right)}}{ \tan{ \left( \frac{1}{2} (A+B) \right)}}
```


LORENTZ TRANSFORMATION

```latex
{x}' = \frac{x -  v·t}{\sqrt{1-\frac{v^{2}}{c^{2}} }}
```

```latex
{t}' = \frac{t -  x·\frac{v}{c^{2}}}{\sqrt{1-\frac{v^{2}}{c^{2}} }}
```

FUNDAMENTAL TRIGONOMETRY EQUATIONS:

```latex
\sin ^{2} + \cos ^{2} = 1
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/trig_fundamental_eq.svg?sanitize=true" alt="fundamental equation of trigonometry">
<br>


```latex
1 + \tan^{2} = \sec^{2}
```
<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/tang_eq.svg?sanitize=true" alt="fundamental equation squared tangent">
<br>

```latex
1 + \cot^{2} = \csc^{2}
```
<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/cotang_eq.svg?sanitize=true" alt="fundamental equation squared contangent">
<br>


CONICS:

```latex
( x- x_{0})^{2} + (y - y_{0})^{2} = R^{2}
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/circunf_eq.svg?sanitize=true" alt="circunference equation">
<br>




SPIRAL, (archimedean spiral, 
<!--http://www.mathematische-basteleien.de/spiral.htm -->

Parametric:
 x(t) = R cos(t), y(t) = R sin(t), R = kte · t;

Cartesian:
x²+y² = a²[arc tan (y/x)]²
 
 EQUIANGULAR SPIRAL (LOGARITMIC SPIRAL, BERNOULLI SPIRAL)
 
Parametric:
  x(t) = R cos(t), y(t) = R sin(t), R = kte · exp(t) ;

Cartesian:
 y = x tan[ln(sqr(x²+y²))]
 
 More spirals:
 
 r= t^2  (Paraboilc or Fermat Spiral)
 r = ln(t)  (Lituus spiral)
 r = +/- sqrt(t)
 r = 1 / t
 r = 1 / sqrt(t)


LOXODROME: The curve on the sphere that crosses the meridians at constant angle. In the mercator proyection they appear as straight lines.

x=cos(t) cos [1/tan (Kte·t)] 
y=sin(t) cos[1/tan (Kte·t)] 
z= -sin [1/tan (Kte·t)]    


ASTROID:

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/astroid_eq_2.svg?sanitize=true" alt="circunference equation">
<br>

```latex
\begin{matrix}
\textrm{cartesian} & 
x^{\frac{2}{3}} + y^{\frac{2}{3}} = a^{\frac{2}{3}}
\\ 
\textrm{polar} & \left\{\begin{matrix}
 x = a \cos^3(t)
\\ y = a \sin^3(t)
\end{matrix}\right.
\end{matrix}
```

CICLOID:

```latex
\mathrm{ordinary  \; \;cicloid  \; \;(a=1)} \; \; \; \;
\left\{\begin{matrix}
x =& t- a \sin t  \\ 
y =& 1 - a \cos t
\end{matrix}\right.
```

TALBOT:

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/curve_talbot.svg?sanitize=true" alt="circunference equation">
<br>

```latex
\left\{\begin{matrix}
x = \big(k^2  + f^2· \sin (t) \big) \cdot \frac{  \cos (t) }{k}  \\ 
y = \big(  k^2 - 2·f^2 + f^2· \sin (t)  \big)  \cdot \frac{ sin(t) }{b}
\end{matrix}\right.
```

```latex
\left\{\begin{matrix}
x =& \big(k^2  + f^2· \sin (t) \big) \cdot \frac{  \cos (t) }{k}  \\ 
y =& \big(  k^2 - 2·f^2 + f^2· \sin (t)  \big)  \cdot \frac{ sin(t) }{b}
\end{matrix}\right.
```


TWO DIMENSIONS

POINTS

```latex
P1(x_1,y_1) = x_1 \overrightarrow{i} + y_1 \overrightarrow{j}
```
<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/Point1_3.svg?sanitize=true" alt="distance between two points formula">
<br>

DISTANCE BETWEEN TWO POINTS

```latex
d = \sqrt{ (x1-x2)^2 + (y1-y2)^2 }
```

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/distancetwopoints2.svg?sanitize=true" alt="distance between two points formula">
<br>

COLINIALITY: three points are colineal if the following determinat equations is true.


```latex
\begin{vmatrix}
x_1 & y_1 & 1\\ 
x_2 & y_2 & 1\\ 
x_3 & y_3 & 1
\end{vmatrix} = 1
```
<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/3pointscoliniality2.svg?sanitize=true" alt="three points coliniality equation">
<br>


LINES

GENERAL FORM

```latex
\begin{matrix}
Ax + By + C = 0
\\  \forall A, B, C \,  \epsilon  \, \mathbb{R}
\\ A \neq 0 \wedge B \neq 0
\end{matrix}
```


<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/line_general_form.svg?sanitize=true" alt="line general form equation">
<br>


TWO POINTS EQUATION

```latex
\frac{ x - x_1}{ y_2 - y_1} =  \frac{ y - y_1}{ x_2 - x_1} 
```

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/line_2points.svg?sanitize=true" alt="line two points equation">
<br>


INTERCEPT FORM

```latex
\frac{x}{a} + \frac{y}{b} = 1
```

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/line_intercept_form.svg?sanitize=true" alt="line intercept equation">
<br>

NORMAL FORM

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/line_normal_form.svg?sanitize=true" alt="line normal form equation">
<br>


PARAMETRIC FORM

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/line_parametric_forl.svg?sanitize=true" alt="line parametric form equation">
<br>


SLOPE FORM

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/line_slope.svg?sanitize=true" alt="line slope form equation">
<br>


SLOPE POINT FORM

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/line_point_slope.svg?sanitize=true" alt="line slope point form equation">
<br>

DISTANCE BETWEEN A POINT AND A LINE

The distance between a line and a point is given by:


<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/line_point_distance.svg?sanitize=true" alt="distance between line and point">
<br>

CROSSING POINT OF TWO LINES

```latex
\begin{matrix}
&
\left\{\begin{matrix}
 r_1 \equiv A_1 x + B_1 y + C_1 = 0 
\\ 
r_2 \equiv A_2 x + B_2 y + C_2 = 0 
\end{matrix}\right.

\\ \\& P = r_1 \cap r_2 = (x,y)

\\ \\ & x= \frac{-C_1 B_2 + C_2 B1}{A_1 B_2 - A_2 B_1}
\\
\\ & y= \frac{-A_1 C_2 + A_2 C_1}{A_1 B_2 - A_2 B_1}

\end{matrix}
```

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/lines_crossing.svg?sanitize=true" alt="distance between line and point">
<br>


3 CONCURRENT LINES

```latex
\begin{matrix}
&
\left\{\begin{matrix}
 r_1 \equiv A_1 x + B_1 y + C_1 = 0 
\\ 
r_2 \equiv A_2 x + B_2 y + C_2 = 0 
\\ 
r_3 \equiv A_3 x + B_3 y + C_3 = 0 
\end{matrix}\right.
\\
& \exists \:  P = r_1 \cap r_2 \cap r_3 = (x,y) \neq \oslash  \Leftrightarrow 

 \begin{vmatrix}
 A_1 &B_1 &C_1 \\ 
 A_2 &B_2 &C_2 \\
 A_3 &B_3 &C_3
\end{vmatrix} = 0
\end{matrix}
```

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/lines_3_concurrent.svg?sanitize=true" alt="condition for concurrence of three lines">
<br>

LINE SEGMENT

A line segment can be defined as:

```latex
\begin{matrix}
x = x_1 + (x_2-x_1)t
\\ y = y_1 + (y_2-y_1)t
\\ 0 \leq  t \leq  1
\end{matrix}
```

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/line_segment.svg?sanitize=true" alt="equation for a line segment">
<br>

BISECTOR OF A SEGMENT

The perpendicular bisector of a segment, defined by it's two points P1 and P2, is defined by the line equation:

```latex
(x_2-x_1)\cdot x + (y_2-y_1)\cdot y - \frac{[(x_2^2+y_2^2) - (x_1^2+y_1^2)]}{2} = 0.
```

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/line_sector_bisector.svg?sanitize=true" alt="equation a segment's bisector">
<br>

TWO SEGMENTS INTERCEPTION

```latex
\begin{matrix}
 \exists  \overline{P1\, P2} \cap \overline{P3\, P4}  \leftrightarrow 
 \exists \: s,\, t:  ( 0 \leq s \leq 1 ) \wedge (0 \leq t \leq 1)
\\ 
\\
\left\{\begin{matrix}
x_1 + (x_2 - x_1)t = x_3 + (x_4 - x_3)s
\\ 
y_1 + (y_2 - y_1)t = y_3 + (y_4 - y_3)s
\end{matrix}\right.
\\ 
\\
s = \frac{\begin{vmatrix} x_2 - x_1
 & y_2 - y_1 \\ x_3 - x_1
 & y_3 - y_1
\end{vmatrix}}{\begin{vmatrix} x_2 - x_1
 & y_2 - y_1 \\ x_3 - x_4
 & y_3 - y_4
\end{vmatrix} }
\\
\\
t = \frac{\begin{vmatrix} x_3 - x_1
 & y_3 - y_1 \\ x_3 - x_4
 & y_3 - y_4
\end{vmatrix}}{\begin{vmatrix} x_2 - x_1
 & y_2 - y_1 \\ x_3 - x_4
 & y_3 - y_4
\end{vmatrix} }

\end{matrix}
```

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/lines_segments_intercepts.svg?sanitize=true" alt="existence of two segment's bisector">
<br>



AREA OF A TRIAGLE

The area of a triangle defined by three lines is:

```latex
A = \frac{ 
\begin{matrix} 
 \begin{vmatrix}
     A_1 &  B_1 & C_1
 \\  A_2 &  B_2 & C_2
 \\  A_3 &  B_3 & C_3
\end{vmatrix}^2
\\ \: 
\end{matrix}
 }
{\begin{matrix} 
\: \\ 
2 
\begin{vmatrix} A_1 & B_1 \\  A_2 & B_2
\end{vmatrix} 

\begin{vmatrix} A_2 & B_2 \\  A_3 & B_3
\end{vmatrix} 

\begin{vmatrix} A_3 & B_3 \\ A_1 & B_1 
\end{vmatrix} 
\end{matrix}
}
```
<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/three_lines_def.svg?sanitize=true" alt="definition of 3 lines">
<br>


<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/area_triangle_01.svg?sanitize=true" alt="area of a triangle defined by 3 lines">
<br>



For a triagle defined by the vertices P1, P2 and P3, its area is defined by:

```latex
A = 
\frac{1}{2}
 \begin{vmatrix}
     x_1 &  y_1 & 1
 \\  x_2 &  y_2 & 1
 \\  x_3 &  y_3 & 1
 \end{vmatrix}
```

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/area_triangle_02.svg?sanitize=true" alt="area of a triangle defined by 3 vertices">
<br>

or also by:

<br>
<img  src="https://github.com/sergiocollado/potpourri/blob/master/image/area_triangle_03.svg?sanitize=true" alt="area of a triangle defined by 3 vertices 2">
<br>

CURVATURE FUNCTION

```latex
\frac{1}{R} = \frac{ \left | f{(x)}'' \right | }{\left (1 +   \left [ f{(x)}' \right ]^{2}  \right )^{\frac{3}{2}}}
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/curvature.svg?sanitize=true" alt="curvature of a function">
<br>


MATRIX TRANSFORMATION

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/2dmatrixScale.svg?sanitize=true" alt="2D matrix scale operation">
<br>

```latex
\mathrm{2D\:  Scale:\; \; }   \; \; S= \begin{pmatrix}
S_x & 0 \\ 
0 & S_y
\end{pmatrix}
```


<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/2dmatrixScaleInv.svg?sanitize=true" alt="2D Scale matrix inverse">
<br>

```latex
S^{-1}= \begin{pmatrix}
S_x^{-1} & 0 \\ 
0 & S_y^{-1}
\end{pmatrix}
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/2dmatrixShear.svg?sanitize=true" alt="2D shear matrix">
<br>


```latex
\mathrm{2D\:  Shear:\; \; }   \; \; Shear= \begin{pmatrix}
1 & a \\ 
0 & 1
\end{pmatrix}
```

```latex
Shear^{-1}= \begin{pmatrix}
1 & -a \\ 
0 & 1
\end{pmatrix}
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/2dmatrixRotation.svg?sanitize=true" alt="2D Rotation matrix">
<br>

```latex
\mathrm{2D\:  Rotation:\; \; }   \; \; R= \begin{pmatrix}
\cos(\theta)  & -\sin(\theta) \\ 
\sin(\theta) & \cos(\theta)
\end{pmatrix}
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/2dmatrixPropierties2.svg?sanitize=true" alt="2D propierties matrix">
<br>

R is orthogonal, meaning: R^T · R = I


```latex
\begin{align*}
M &= M_1 M_2 M_3\\ 
M^{-1} &= M_3^{-1} M_2^{-1} M_1^{-1}
\\ 
M^{-1} M &= M_3^{-1} ( M_2^{-1} ( M_1^{-1} M_1) M_2) M_3
\end{align*}
```

```latex
\begin{matrix}
M = M_1 M_2 M_3\\ 
M^{-1} = M_3^{-1} M_2^{-1} M_1^{-1}
\\ 
M^{-1} M = M_3^{-1} ( M_2^{-1} ( M_1^{-1} M_1) M_2) M_3
\end{matrix}
```
<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/3dmatrixRX.svg?sanitize=true" alt="3D Rotation Y axis matrix">
<br>

```latex
\mathrm{3D \; \; x\; \;  Rotation:} \; \; \; \; R_x= \begin{pmatrix}
\1 &\0 &\0 \\
\0 &\cos(\theta)  &-\sin(\theta) \\ 
\0 &\sin(\theta) & \cos(\theta) 0
\end{pmatrix}
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/3dmatrixRY.svg?sanitize=true" alt="3D Rotation y matrix">
<br>

```latex
\mathrm{3D \; \; y\; \;  Rotation:} \; \; \; \; R_y= \begin{pmatrix}
cos\theta &\0 &\sin\theta \\ 
\0 &1 &0 \\
-\sin\theta &0 &\cos\theta
\end{pmatrix}
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/3dmatrixRZ.svg?sanitize=true" alt="3D Rotation z matrix">
<br>

```latex
\mathrm{3D \; \; y\; \;  Rotation:} \; \; \; \; R_y= \begin{pmatrix}
cos\theta &\0 &\sin\theta \\ 
\0 &1 &0 \\
-\sin\theta &0 &\cos\theta
\end{pmatrix}
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/orthogonal_matrixes.svg?sanitize=true" alt="Orthogonal mtrix eq">
<br>

```latex
\mathrm{Orthogonal \; matrix:\: \: \: } \; \; R^T \cdot R = I
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/3dmatrixRotLinear.svg?sanitize=true" alt="Orthogonal mtrix eq">
<br>

```latex
\mathrm{Rotation \;is  \; linear:\: \: \: } \; \; R\cdot ( X + Y ) = R \cdot X + R \cdot Y
```

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/3dnewCoorSys.svg?sanitize=true" alt="New coord system">
<br>

```latex
\left\{\begin{matrix}
\vec{u} = ( x_u, y_u, z_u)\\ 
\vec{v} = ( x_v, y_v, z_v)\\ 
\vec{w} = ( x_w, y_w, z_w)
\end{matrix}\right.
```
<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/3dmatrixPointRotation.svg?sanitize=true" alt="3d Point rotation">
<br>

```latex
R_p = \begin{pmatrix}
x_u &y_u  &z_u \\ 
x_v &y_v  &z_v \\ 
x_w &y_w  &z_w
\end{pmatrix}
\cdot 
\begin{pmatrix}
x_p\\ 
y_p\\ 
z_p
\end{pmatrix}
= \begin{pmatrix}
\vec{u} \cdot p\\ 
\vec{v} \cdot p\\
\vec{w} \cdot p
\end{pmatrix}
```

3D TRANSLATION: HOMOGENEUS COORDENATES

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/3dmatrixHomogeneusCoord.svg?sanitize=true" alt="3d Point rotation">
<br>

```latex
\begin{pmatrix} x'\\ y'\\ z'\\ w' \end{pmatrix} 
= 
\begin{pmatrix}
\1 &0 &0  &k\\
\0 &1 &0  &0\\
\0 &0 &1  &0\\
\0 &0 &0  &1
\end{pmatrix} 
\cdot 
\begin{pmatrix} x\\ y\\ z\\ 1\end{pmatrix}
= 
\begin{pmatrix} x+k\\ y\\ z\\ w \end{pmatrix}
```
GENERAL TRANSLATION

<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/3dmatrixHomogeneusCoordTrasnslation.svg?sanitize=true" alt="3d general translation">
<br>

```latex
\begin{pmatrix} x'\\ y'\\ z'\\ w' \end{pmatrix} = \begin{pmatrix}
\1 &0 &0  &Tx\\
\0 &1 &0  &Ty\\
\0 &0 &1  &Tz\\
\0 &0 &0  &1
\end{pmatrix} 
\cdot 
\begin{pmatrix} x\\ y\\ z\\ 1\end{pmatrix}
= 
\begin{pmatrix} x+Tx\\ y+Ty\\ z+Tz\\ 1 \end{pmatrix}
```
COMBINATION OF ROTATiONS, AND TRANSLATIONS

R·T != T·R 

P'=(T·R)P = M·P = R·P + T

P'=(R·T)P = M·P = R·(P+T) = R·P + R·T


<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/3dmatrixTR.svg?sanitize=true" alt="3d general translation">
<br>

```latex
\begin{matrix}
 P' = (T\cdot R)\cdot P = M\cdot P = R\cdot P + T  \\
\\
M = 
\begin{pmatrix}
\1 &0 &0  &Tx\\
\0 &1 &0  &Ty\\
\0 &0 &1  &Tz\\
\0 &0 &0  &1
\end{pmatrix} 
\cdot 
\begin{pmatrix}
\ R_{11} &R_{12} &R_{13}  &0\\
\ R_{21} &R_{22} &R_{23}  &0\\
\ R_{31} &R_{32} &R_{33}  &0\\
\0 &0 &0  &1
\end{pmatrix} 
= 
\begin{pmatrix}
\ R_{11} &R_{12} &R_{13}  &Tx\\
\ R_{21} &R_{22} &R_{23}  &Ty\\
\ R_{31} &R_{32} &R_{33}  &Tz\\
\0 &0 &0  &1
\end{pmatrix} 
\end{matrix}
```


<br>
<img  src="https://rawgit.com/sergiocollado/potpourri/master/image/3dmatrixRT.svg?sanitize=true" alt="3d general translation">
<br>

```latex
\begin{matrix}
 P' = (R\cdot T)\cdot P = M\cdot P = R\cdot( P + T ) = R \cdot P + R \cdot T \\
\\
M = 
\begin{pmatrix}
\ R_{11} &R_{12} &R_{13}  &0\\
\ R_{21} &R_{22} &R_{23}  &0\\
\ R_{31} &R_{32} &R_{33}  &0\\
\0 &0 &0  &1
\end{pmatrix} 
\cdot 
\begin{pmatrix}
\1 &0 &0  &Tx\\
\0 &1 &0  &Ty\\
\0 &0 &1  &Tz\\
\0 &0 &0  &1
\end{pmatrix} 
= 
\begin{pmatrix}
\ R_{3x3} &R_{3x3} \cdot T_{3x1}\\
\ 0_{1x3} &1 
\end{pmatrix} 
\end{matrix}
```



```latex
\begin{matrix}
y= Cte  \;\;\;\; &y'= 0  \\ 
y= Cte \cdot u \;\;\;\;&y'= Cte \cdot u' \\ 
y = f(u)\;\;and\;\; u = g(x) \;\;\;\;&  y' = \frac{dy}{dx} = \frac{df}{du} \cdot \frac{du}{dx}\\ 
y= u \pm v \pm w\cdots  \;\;\;\;&y'= u' \pm v' \pm w' \cdots \\ 
y= u\cdot v \;\;\;\;&y' = u'\cdot v + u\cdot v' \\ 
y= \frac{u}{v} \;\;\;\;&y=\frac{u'\cdot v - u\cdot v}{v^2} \\ 
y= Cte \cdot x^{n} \;\;\;\;&y' = Cte \cdot n \cdot x^{n-1} \\ 
y= Cte \cdot e^{n} \;\;\;\;&y' = Cte \cdot e^{n} \\ 
y= Ln(x) \;\;\;\;&  y' = \frac{1}{x} \\ 
y= \sin{x} \;\;\;\;&  y' = \cos{x} \\ 
y= \cos{x} \;\;\;\;&  y' = -\sin{x} \\ 
 \;\;\;\;& \\ \sin 
 \;\;\;\;& \\ 
 \;\;\;\;& \\ 
 \;\;\;\;& \\ 
 \;\;\;\;& \\  
 \;\;\;\;& \\ 
 \;\;\;\;& \\ 
 \;\;\;\;& \\ 
 \;\;\;\;& \\ 
 \;\;\;\;& 
\end{matrix}
```
