//Paillier Cryptosystem by 1807034 (Waliul Islam Sumon)

import java.math.BigInteger;
import java.util.Scanner;
import java.lang.Math;

public class Paillier {

	public static void main(String[] args) {
		BigInteger x1, x2, n2, msg, cyp, dec, p, q, n, phi_n, g, lembda, mu, r;
		
		p = new BigInteger("656692050181897513638241554199181923922955921760928836766304161790553989228223793461834703506872747071705167995972707253940099469869516422893633357693");
		q = new BigInteger("204616454475328391399619135615615385636808455963116802820729927402260635621645177248364272093977747839601125961863785073671961509749189348777945177811");
		n = p.multiply(q);
		x1 = p.subtract(new BigInteger("1"));
		x2 = q.subtract(new BigInteger("1"));
		phi_n = x1.multiply(x2);
		lembda = LCM(x1, x2);
		n2 = n.multiply(n);
		
		g = chooseG(n);
		mu = chooseMu(g, lembda, n);
		
		System.out.println("Public Key (n, g): " + n + " " + g);
		System.out.println("Private Key (lambda, mu): " + lembda + " " + mu);
		
		r = BigInteger.valueOf(chooseR(n));
		
		msg = new BigInteger("1111111111111111111111111111111111111111111111111111111111");
		System.out.println("The Message: " + msg);
		x1 = pow_big(g, msg, n2);
		x2 = pow_big(r, n, n2);
		cyp = (x1.multiply(x2)).mod(n2);
		System.out.println("The Encrypted Message: " + cyp);
		x1 = L(pow_big(cyp, lembda, n2), n);
		dec = ((x1.mod(n)).multiply(mu.mod(n))).mod(n);
		System.out.println("The Decrypted Message: " + dec);

	}
	
	public static BigInteger LCM(BigInteger a, BigInteger b)
	{
		BigInteger gcd_val = GCD(a, b);
		return (a.divide(gcd_val)).multiply(b);
	}
	
	public static BigInteger chooseG(BigInteger n)
	{
		BigInteger n2, i;
		n2 = n.multiply(n);
		for(i = new BigInteger("2"); i.compareTo(n2) < 0; i.add(BigInteger.ONE))
			if((GCD(i, n2).equals(BigInteger.ONE)))
					return i;
		return i;
	}
	
	public static BigInteger chooseMu(BigInteger g, BigInteger lembda, BigInteger n)
	{
		BigInteger n2, x, b, mu;
		n2 = n.multiply(n);
		x = pow_big(g, lembda, n2);
		b = L(x, n);
		mu = mod_inverse(b, n);
		return mu;
	}
	
	public static int chooseR(BigInteger n)
	{
		int lb, ub, r;
		lb = 15;
		ub = 155;
		r = (int)((Math.random()*(ub - lb + 1) + lb));
		while((GCD(n, BigInteger.valueOf(r)).compareTo(BigInteger.ONE) != 0))
			r = (int)((Math.random()*(ub - lb + 1) + lb));
		return r;
	}
	
	public static BigInteger L(BigInteger x, BigInteger n)
	{
		return (x.subtract(BigInteger.ONE)).divide(n);
	}
	
	public static BigInteger GCD(BigInteger a, BigInteger b)
	{
		if(a.compareTo(b) < 0)
		{
			BigInteger temp;
			temp = a;
			a = b;
			b = temp;
		}
		BigInteger c;
		c = a.mod(b);
		if(c.equals(BigInteger.ZERO))
			return b;
		return GCD(b, c);
	}
	
	public static BigInteger x, y;
	
	public static BigInteger mod_inverse(BigInteger a, BigInteger n)
	{
		BigInteger g = gcdExtended(a, n);
		BigInteger res = ((x.mod(n)).add(n)).mod(n);
		return res;
		
	}
	
	public static BigInteger gcdExtended(BigInteger a, BigInteger b)
	{
		if(b.equals(BigInteger.ZERO))
		{
			x = BigInteger.ONE;
			y = BigInteger.ZERO;
			return a;
		}
		
		BigInteger g = gcdExtended(b, a.mod(b));
		BigInteger x1 = x;
		BigInteger y1 = y;
		BigInteger temp = (a.divide(b)).multiply(y1);
		
		x = y1;
		y = x1.subtract(temp);
		
		return g;
	}
	
	public static BigInteger pow_big(BigInteger a, BigInteger b, BigInteger n)
	{
		if(b.equals(BigInteger.ZERO))
			return BigInteger.ONE;
		if((b.mod(new BigInteger("2"))).equals(BigInteger.ZERO))
		{
			BigInteger result;
			result = pow_big(a, b.divide(new BigInteger("2")), n);
			return ((result.mod(n)).multiply(result.mod(n))).mod(n);
		}
		else
		{
			BigInteger result, x1, x2, x3;
			x1 = a.mod(n);
			x2 = pow_big(a, b.subtract(BigInteger.ONE), n).mod(n);
			result = (x1.multiply(x2)).mod(n);
			return result;
		}
	}

}
