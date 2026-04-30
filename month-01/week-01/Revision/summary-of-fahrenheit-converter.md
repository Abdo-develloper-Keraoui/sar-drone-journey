abdottawab@DESKTOP-PC405N0:~/projects/sar-drone-journey/month-01/week-01/ch01/subCh-02$ gcc -Wall
-o ex01-04 ex01-04.c && ./ex01-04
celsius fahr
-30.00  -22.00
-20.00  -4.00
-10.00  14.00
0.00    32.00
10.00   50.00
20.00   68.00
30.00   86.00
40.00   104.00
50.00   122.00
60.00   140.00
70.00   158.00
80.00   176.00
90.00   194.00
100.00  212.00
110.00  230.00
120.00  248.00
130.00  266.00
140.00  284.00
150.00  302.00
abdottawab@DESKTOP-PC405N0:~/projects/sar-drone-journey/month-01/week-01/ch01/subCh-02$ micro ex01-04.c
abdottawab@DESKTOP-PC405N0:~/projects/sar-drone-journey/month-01/week-01/ch01/subCh-02$ gcc -Wall -o ex01-04 ex01-04.c && ./ex01-04
celsius fahr
-30.00  -22.00
-25.00  -13.00
-20.00  -4.00
-15.00  5.00
-10.00  14.00
-5.00   23.00
0.00    32.00
5.00    41.00
10.00   50.00
15.00   59.00
20.00   68.00
25.00   77.00
30.00   86.00
35.00   95.00
40.00   104.00
45.00   113.00
50.00   122.00
55.00   131.00
60.00   140.00
65.00   149.00
70.00   158.00
75.00   167.00
80.00   176.00
85.00   185.00
90.00   194.00
95.00   203.00
100.00  212.00
105.00  221.00
110.00  230.00
115.00  239.00
120.00  248.00
125.00  257.00
130.00  266.00
135.00  275.00
140.00  284.00
145.00  293.00
150.00  302.00
abdottawab@DESKTOP-PC405N0:~/projects/sar-drone-journey/month-01/week-01/ch01/subCh-02$ micro ex01-04.c
abdottawab@DESKTOP-PC405N0:~/projects/sar-drone-journey/month-01/week-01/ch01/subCh-02$ micro ex01-04.c
abdottawab@DESKTOP-PC405N0:~/projects/sar-drone-journey/month-01/week-01/ch01/subCh-02$ gcc -Wall -o ex01-04 ex01-04.c && ./ex01-04
celsius fahr
-30.00  -22.00
-27.00  -16.60
-24.00  -11.20
-21.00  -5.80
-18.00  -0.40
-15.00  5.00
-12.00  10.40
-9.00   15.80
-6.00   21.20
-3.00   26.60
0.00    32.00
3.00    37.40
6.00    42.80
9.00    48.20
12.00   53.60
15.00   59.00
18.00   64.40
21.00   69.80
24.00   75.20
27.00   80.60
30.00   86.00
33.00   91.40
36.00   96.80
39.00   102.20
42.00   107.60
45.00   113.00
48.00   118.40
51.00   123.80
54.00   129.20
57.00   134.60
60.00   140.00
63.00   145.40
66.00   150.80
69.00   156.20
72.00   161.60
75.00   167.00
78.00   172.40
81.00   177.80
84.00   183.20
87.00   188.60
90.00   194.00
93.00   199.40
96.00   204.80
99.00   210.20
102.00  215.60
105.00  221.00
108.00  226.40
111.00  231.80
114.00  237.20
117.00  242.60
120.00  248.00
123.00  253.40
126.00  258.80
129.00  264.20
132.00  269.60
135.00  275.00
138.00  280.40
141.00  285.80
144.00  291.20
147.00  296.60
150.00  302.00



### As we can see from the numbers above when we change the step the numbers change, like the numbers 
### after the comma here  are due to the formula and the value of step used !!

```c
int main(void) 
{
	float fahr, celsius;

	float lower, upper, step;//these are celsius!!

	upper = 150.0;
	lower = -30.0;
	step = 3.0;

	celsius = lower;
	printf("celsius\tfahr\n");
	
	while(celsius <= upper) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%3.2f\t%3.2f\n", celsius, fahr);
		celsius = celsius + step;	
	}
	return 0;
}
```
