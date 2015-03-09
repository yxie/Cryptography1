import java.math.BigInteger;
import java.util.Hashtable;
public class prime {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String sp = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171";
		String sg = "11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568";	
		String sh = "3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333";
		BigInteger p = new BigInteger(sp);
		BigInteger g = new BigInteger(sg);
		BigInteger h = new BigInteger(sh);
		h = h.mod(p);
		int Bint = (int) Math.pow(2, 20);
		BigInteger B = BigInteger.valueOf(Bint);
		Hashtable<BigInteger, BigInteger> ht = new Hashtable<BigInteger, BigInteger>();
		for(int i=0; i<Math.pow(2,20); i++){
			BigInteger x1 = BigInteger.valueOf(i);
			BigInteger gtox1 = g.modPow(x1,p);
			BigInteger gtox1_inv = gtox1.modInverse(p);
			BigInteger left = h.multiply(gtox1_inv);
			left = left.mod(p);
			ht.put(left, x1);
		}
		StdOut.println("hash completed...");
		
		for(int i=0; i<Math.pow(2, 20); i++){
			BigInteger x0 = BigInteger.valueOf(i);
			BigInteger Bx0 = x0.multiply(B);
			BigInteger gBx0 = g.modPow(Bx0,p);
			if(ht.containsKey(gBx0) == true){
				String x0s = x0.toString();
				String x1s = ht.get(gBx0).toString();
				StdOut.println(x0s);
				StdOut.println(x1s);
				StdOut.println("find x0 x1");
			}
		}
		StdOut.println("finished...");
		
	}

}
