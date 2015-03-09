import urllib2
import sys

TARGET = 'http://crypto-class.appspot.com/po?er='
#--------------------------------------------------------------
# padding oracle
#--------------------------------------------------------------
class PaddingOracle(object):
    def query(self, q):
        target = TARGET + urllib2.quote(q)    # Create query URL
        req = urllib2.Request(target)         # Send HTTP request to server
        try:
            f = urllib2.urlopen(req)          # Wait for response
        except urllib2.HTTPError, e:          
            print "We got: %d" % e.code       # Print response code
            if e.code == 404:
                return True # good padding
            return False # bad padding
        

def strxor(a, b):    # xor two hex strings of the same length
    return "".join(["%x" % (int(x,16) ^ int(y,16)) for (x, y) in zip(a, b)])

def int2hex(a, i):
    hexcode = list('0123456789abcdef');
    low = hexcode[a % 16];
    high = hexcode[a / 16];
    return i*"".join(high+low);
    
if __name__ == "__main__":
    po = PaddingOracle()

    a = "546865204d6167696320576f726473206172652053717565616d697368204f7373696672616765";
    print a.decode("hex");
    raw_input("Finish m2")
        
    
    url1 = list('f20bdba6ff29eed7b046d1df9fb70000');
    url2 = list('58b1ffb4210a580f748b4ac714c001bd');
    url3 = list('4a61044426fb515dad3f21f18aa577c0');
    url4 = list('bdf302936266926ff37dbf7035d5eeb4');

    url1_m = list('f20bdba6ff29eed7b046d1df9fb70000');
    url2_m = list('58b1ffb4210a580f748b4ac714c001bd');
    url3_m = list('4a61044426fb515dad3f21f18aa577c0');
    url4_m = list('bdf302936266926ff37dbf7035d5eeb4');

    m1 = list('f20bdba6ff29eed7b046d1df9fb70000');
    m2 = list('58b1ffb4210a580f748b4ac714c001bd');
    m3 = list('4a61044426fb515dad3f21f18aa577c0');
    m4 = list('bdf302936266926ff37dbf7035d5eeb4');
    
    good_guess = ""; 
    for i in range(0, 16):
        for g in range(0, 256):
            guess = int2hex(g, 1) + good_guess;
            print g
            temp = "".join(url1[(15-i)*2:]);
            temp = strxor(temp, guess);
            temp = strxor(temp, int2hex(i+1, i+1));
            index = (15-i)*2;
            while index < 32:
                url1_m[index] = temp[index-(15-i)*2];
                index = index + 1;
            
            url_all = "".join(url1_m + url2_m)
            if po.query(url_all):        # Issue HTTP query with the given argument
                m2[(15-i)*2] = guess[0];
                m2[(15-i)*2+1] = guess[1];
               # print "".join(m4)
               # print url_all
                print "".join(url1_m)
                good_guess = guess;
               # raw_input("Press ENTER to exit")
                break

    print good_guess
    raw_input("Finish m2")

    url1 = list('f20bdba6ff29eed7b046d1df9fb70000');
    url2 = list('58b1ffb4210a580f748b4ac714c001bd');
    url3 = list('4a61044426fb515dad3f21f18aa577c0');
    url4 = list('bdf302936266926ff37dbf7035d5eeb4');

    url1_m = list('f20bdba6ff29eed7b046d1df9fb70000');
    url2_m = list('58b1ffb4210a580f748b4ac714c001bd');
    url3_m = list('4a61044426fb515dad3f21f18aa577c0');
    url4_m = list('bdf302936266926ff37dbf7035d5eeb4');

    m1 = list('f20bdba6ff29eed7b046d1df9fb70000');
    m2 = list('58b1ffb4210a580f748b4ac714c001bd');
    m3 = list('4a61044426fb515dad3f21f18aa577c0');
    m4 = list('bdf302936266926ff37dbf7035d5eeb4');
    
    good_guess = ""; 
    for i in range(0, 16):
        for g in range(0, 256):
            guess = int2hex(g, 1) + good_guess;
            print g
            temp = "".join(url2[(15-i)*2:]);
            temp = strxor(temp, guess);
            temp = strxor(temp, int2hex(i+1, i+1));
            index = (15-i)*2;
            while index < 32:
                url2_m[index] = temp[index-(15-i)*2];
                index = index + 1;
            
            url_all = "".join(url1_m + url2_m + url3_m)
            if po.query(url_all):        # Issue HTTP query with the given argument
                m3[(15-i)*2] = guess[0];
                m3[(15-i)*2+1] = guess[1];
               # print "".join(m4)
               # print url_all
                print "".join(url2_m)
                good_guess = guess;
               # raw_input("Press ENTER to exit")
                break

    
    print good_guess
    raw_input("Finish m3")

    url1 = list('f20bdba6ff29eed7b046d1df9fb70000');
    url2 = list('58b1ffb4210a580f748b4ac714c001bd');
    url3 = list('4a61044426fb515dad3f21f18aa577c0');
    url4 = list('bdf302936266926ff37dbf7035d5eeb4');

    url1_m = list('f20bdba6ff29eed7b046d1df9fb70000');
    url2_m = list('58b1ffb4210a580f748b4ac714c001bd');
    url3_m = list('4a61044426fb515dad3f21f18aa577c0');
    url4_m = list('bdf302936266926ff37dbf7035d5eeb4');

    m1 = list('f20bdba6ff29eed7b046d1df9fb70000');
    m2 = list('58b1ffb4210a580f748b4ac714c001bd');
    m3 = list('4a61044426fb515dad3f21f18aa577c0');
    m4 = list('bdf302936266926ff37dbf7035d5eeb4');

    
    good_guess = "090909090909090909";
    for i in range(9, 16):
        for g in range(0, 256):
            guess = int2hex(g, 1) + good_guess;
            print g
            temp = "".join(url3[(15-i)*2:]);
            #print temp
            #print guess
            temp = strxor(temp, guess);
            temp = strxor(temp, int2hex(i+1, i+1));
            #print int2hex(i+1, i+1)
            #print temp
            index = (15-i)*2;
            #raw_input("Press ENTER to exit")
            while index < 32:
                url3_m[index] = temp[index-(15-i)*2];
                index = index + 1;
            
            url_all = "".join(url1_m + url2_m + url3_m + url4_m)
            if po.query(url_all):        # Issue HTTP query with the given argument
                m4[(15-i)*2] = guess[0];
                m4[(15-i)*2+1] = guess[1];
               # print "".join(m4)
               # print url_all
                print "".join(url3_m)
                good_guess = guess;
               # raw_input("Press ENTER to exit")
                break

    
    print good_guess
    raw_input("Finish m4")
  
