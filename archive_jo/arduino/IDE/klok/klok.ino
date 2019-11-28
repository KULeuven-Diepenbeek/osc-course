/* 
 * IO mapping
 */
int digits[4] = {9, 3, 5, 6};
int segments[7] = {13, 12, 11, 10, 8, 7, 4};
int sevensegencoding[16][7] = {
  //  a     g      b    f     d     e     c
    {HIGH, LOW , HIGH, HIGH, HIGH, HIGH, HIGH}, // 0
    {HIGH, LOW , HIGH, LOW , LOW , LOW , LOW }, // 1
    {HIGH, HIGH, LOW , HIGH, HIGH, LOW , HIGH}, // 2
    {HIGH, HIGH, HIGH, HIGH, LOW , LOW , HIGH}, // 3
    {HIGH, HIGH, HIGH, LOW , LOW , HIGH, LOW }, // 4
    {LOW , HIGH, HIGH, HIGH, LOW , HIGH, HIGH}, // 5
    {LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, // 6
    {HIGH, LOW , HIGH, HIGH, LOW , LOW , LOW }, // 7
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, // 8
    {HIGH, HIGH, HIGH, HIGH, LOW , HIGH, HIGH}, // 9
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW }, // 10
    {LOW , HIGH, HIGH, LOW , HIGH, HIGH, HIGH}, // 11
    {LOW , LOW , LOW , HIGH, HIGH, HIGH, HIGH}, // 12
    {HIGH, HIGH, HIGH, LOW , HIGH, LOW , HIGH}, // 13
    {LOW , HIGH, LOW , HIGH, HIGH, HIGH, HIGH}, // 14
    {LOW , HIGH, LOW , HIGH, HIGH, HIGH, LOW }  // 15
  };


/* show a value on a digit */
/*   a: digit
 *   b: value */
void show(int a, int b) {
  int i;
  for (i=0;i<4;i++) {
    if(i==a) {
      digitalWrite(digits[i], LOW);
    } else {
      digitalWrite(digits[i], HIGH);
    }
  }
  for (i=0;i<7;i++) {
    digitalWrite(segments[i], sevensegencoding[b][i]);
  }
}


void setup() {
  int i;

  for(i=0;i<4;i++)
    pinMode(digits[i], OUTPUT);
    
  for(i=0;i<7;i++)
    pinMode(segments[i], OUTPUT);
}


void loop() {
  int i, j, k, l;
  int d[4];

  for(i=0;i<24;i++){
    for(j=0;j<60;j++){
      d[0]= j % 10;
      d[1]= (j-d[0]) / 10;
      d[2]= i % 10;
      d[3]= (i-d[2]) / 10;

      for(k=0;k<100;k++) {
        for(l=0;l<4;l++) {
          show(l, d[l]);
          delay(1);
        }       
      }
  }}
}
