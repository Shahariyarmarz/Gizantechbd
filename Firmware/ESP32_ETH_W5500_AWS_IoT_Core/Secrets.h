#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32_thing"                         //change this
 
const char WIFI_SSID[] = "GizanTech_EXT";               //change this
const char WIFI_PASSWORD[] = "#Analysis23";           //change this
const char AWS_IOT_ENDPOINT[] = "a1lqed3wvcgkf4-ats.iot.us-east-2.amazonaws.com";       //change this "a1r3fvofgk7tm9-ats.iot.us-east-2.amazonaws.com"
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUMAmnerdQUpw7Q8Q+owoqW0Qzi/gwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MDMxODA5Mjky
OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALVECOt3wRZG7Jufs3bo
vqI8eua5VgaPpof+UNo/oW4a8Iv8DwDE8xqo5EBWF90J55fSZ9/BRAW/BycdChe3
j+bzSr3Vt8gc78U0TpVI1LvoSuS+IC6FXL02rj36NxH/xua7bPjIvp0949NNXGVR
3t8jG08CKKHkjcF8lIRmx1HnmpwanK1DvpDd6zQCRCXlTZOOT6PMOkDM+57IZPWk
aED+X3RCVUGBrxL2W8zKNzllEdouLrGwIhp7Gaix9zVN6Oj5YfNNC7oXff7Iaxkh
dciQbyI7mAy3ditxLZzOizoAdgBFbuO6R7DT5Hj/sFTNp6EoyxuHG4owmg+xK6cF
CDsCAwEAAaNgMF4wHwYDVR0jBBgwFoAUUy30RghAoEj+Kbgn4E0Vw1xsmj8wHQYD
VR0OBBYEFEcIV3jTilDFk1fXPlq/qoupAdbiMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAJgqS7+Tnj/Ug7EkXvt7FFTa1n
AF4gC0+x4UW9P7x1DHX+FdzmVKCiXNBKbXZpUEInsCTRpTAFGkLRKSB0G3qAfMbY
/RW1pQos1F2dlhEtKBJ52FIao7nXaHiBxAUikcBWbJtEb2b/bGMyMeFTULjvEed0
ppt4P8luzHkyVbOK6fW0PpKclJyppuyTyb3oK3VfL6FKWZ7UHbstgfK/PxYDdEJ0
tHClK+eNvL9CT8oSuwGEPr2iFxhChbk+ADihPqthNVyK3E516sJnj/OWsHnxcP7p
0wwekbg0GlENJvuu+gunZspRY/n1ph4YoUVCsvchTeYTxOdYsDiJ8Xzdtgd0
-----END CERTIFICATE-----



 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAtUQI63fBFkbsm5+zdui+ojx65rlWBo+mh/5Q2j+hbhrwi/wP
AMTzGqjkQFYX3Qnnl9Jn38FEBb8HJx0KF7eP5vNKvdW3yBzvxTROlUjUu+hK5L4g
LoVcvTauPfo3Ef/G5rts+Mi+nT3j001cZVHe3yMbTwIooeSNwXyUhGbHUeeanBqc
rUO+kN3rNAJEJeVNk45Po8w6QMz7nshk9aRoQP5fdEJVQYGvEvZbzMo3OWUR2i4u
sbAiGnsZqLH3NU3o6Plh800Luhd9/shrGSF1yJBvIjuYDLd2K3EtnM6LOgB2AEVu
47pHsNPkeP+wVM2noSjLG4cbijCaD7ErpwUIOwIDAQABAoIBAAsZcGZivdsMWr6o
x8d3Nv0eMPRh0uex8iOPqgnDLbJdSe94br7AUJaIUvmxi+KIEbtVMfEcl3q2mMyH
Va/gGJquuRvos0k4pGHx8wHnJMeg0L0y+yt+FRCtAXxgDvE2NUq5nVGakTl1qbat
nQPDQJ9vOePboPtQ0HFRnJKC7J+SMZRVrMtJvL075MFQf2zSeYS7++edoAylOxPY
nodlv89F6aFNGfzNip3cqunzFb/QLIiUTn7STAxIsT6WI+M0C0tLk1nGy01Lgw7a
gBK/lT/T0YWvg8wRwH1zMicmTq70/FzmT42psJYN/13HKDjxpVicVbLguwPc5p9E
jlOnfTkCgYEA48B5ittnlnfJVnlK1HLixVM6mOfIuSCsqB7fQdQMGcd4ERUJVTtX
Foo7BmrL7bZegypf6k9/UIXNkb5LwlQecM2dVnOKzOsmVLjnFgh6dmhLMXwHeCQ6
09WGwLKUPEtPWZgisOZfwNcIwnOxBRDOPxz+UCEjvdb1HcGfZ+qCvhUCgYEAy7+L
Tt8opG6Fr6L4M9dgy8tc7EgyONTE7c8pGOxfxeSmdr001cyny0mPE2G8+5BMpLYA
+j+QhBlybNmIj4HR2oRvNI8fogATAzquTYWK3XnY1bLlX6nfB9EekcPb5+PuljG9
yxGfyisXh5fOQRuwahg/xHQkFyveouOGNktqkQ8CgYEAgrb/izCt3XBWwCjRR+nA
OZyxLv0o+QfF0KAXZwK7BziysqsuNhreuvMPOXmmHYLj78gsUKDb421INPPRK3F4
HyoDuZCLA12bHFkbWEv5bWgib/5NkyjIErikpIhaB9j5a+SjVICESHuibWhVGyEw
Ho0XcQn0J4ruF+v+/3dbHpkCgYBXRSD/VHiNDcX3N//F/L+6Ks4PatEQJJqBHdWF
lmFjWw+uFlbWKMXKPiSpcZjHy8P4XPjIN4fH/TpUw0xJ45omVcloItGyywNZw726
+LNFMBafWfQDaLheGcVVPCYqCig8buvTWiYuKwz2CCDRJHIIz4AovnJi9mhzLq9i
/CSWIwKBgQChg/+0d7dn6d2JgySzHKDLeHkqieacYbM5SwdgL5445xgb+6UW2oRm
cDScrT33mLL0ZzbfMhbnB7DDsIltABPlEzBSP6rs5rESxtx/xvO33A2lAz7Nrn7N
PPHXSiJUQHRTlljFHzN35ncOW2khxGlKEC81CyRU5MSx4FV/2tjuUQ==
-----END RSA PRIVATE KEY-----

 
 
)KEY";