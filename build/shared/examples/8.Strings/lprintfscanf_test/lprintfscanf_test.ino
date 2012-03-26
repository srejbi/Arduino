/*
  lprintfscanf_test sketch
  by George Schreiber
  2012.03.26.

  this sketch does nothing but verifies if the binary has been linked with the float-capable versions
  of printf and scanf.

  to link these libraries, a patched version of Arduino IDE (or other options to tweak with the AVR linker options)
  is necessary. 
  
  to go with a patched version of Arduino(TM)-1.0, download and build sources from http://github.com/srejbi/Arduino.git 
  
  then add to the user's Arduino preferences.txt:
    build.linker_options=-Wl,-u,vfprintf,-u,vfscanf,--gc-sections
    build.linker_additional_options=-lprintf_flt -lscanf_flt -lm

  re-compile, upload and enjoy!
*/


boolean testprintf();    // test function for printf
boolean testscanf();     // test function for scanf
void printscan();        // a dummy function that relies on the float-enabled versions of printf/scanf

void setup(void) {
  Serial.begin(57600);
  Serial.println("printf/scanf linking tester");
  if (testprintf() && testscanf()) printscan();
}

void loop(void) {
    // we're done already.
}

// checks printf float behaviour with known value
boolean testprintf()  {
  float ftest = 0;
 
  char sztest[10] ="";
  sprintf(sztest,"%.4f", 2012.0326);        // print 2012.0326 to string
  Serial.print(sztest);
  Serial.print(" - version of printf linked: ");  
  if (sztest[0] == '?') {                                // minimal version
    Serial.println("minimal");
  } else if (strstr(sztest,"2012.0326")==sztest) {       // if float conversion was ok
    Serial.println("float-capable");
    return true;
  } else {                                               // something unexpected happened...
    Serial.println("wtf?");
  }
  return false;
}

// checks sscanf float behaviour with known value
boolean testscanf()  {
  float ftest = 0;
  
  sscanf("2012.0326","%f", &ftest);          // scan 2012.0326 from string
  Serial.print(ftest,4);
  Serial.print(" - version of scanf linked:");  
  if (ftest == 0) {                          // if no value, we have minimal version
    Serial.println("minimal");
  } else if (ftest == 2012.0326 ) {          // if the value matches, we're good
    Serial.println("float-capable");
    return true;
  } else {                                   // expecting the unexpected
    Serial.println("wtf?");
  }
  return false;
}

// happy to print what it scans :)
void printscan() {
  char szbuf[10];
  float tfloat = 0;
  sscanf("2012.0326","%f",&tfloat);
  sprintf(szbuf,"%.4f",tfloat);
  Serial.print("Oh happy day:");
  Serial.println(szbuf);
}

