#In normal RSA, public key for encryption, private key for decryption
#For RSA Digital Signature, Encryption with Private Key, Decryption with Public Key
#public key = e
#private key = d

import hashlib

def gcd(a, b):
    if(b > a):
        a, b = b, a
    c = a % b
    if(c == 0):
        return b
    return gcd(b, c)

def pow_big(a, b, n):
    if b == 0:
        return 1
    if(b % 2 == 0):
        result = pow_big(a, b//2, n)
        return ((result % n) * (result % n)) % n
    else:
        return ((a % n) * (pow_big(a, b - 1, n) % n)) % n
    
    
    
p = 656692050181897513638241554199181923922955921760928836766304161790553989228223793461834703506872747071705167995972707253940099469869516422893633357693
q = 204616454475328391399619135615615385636808455963116802820729927402260635621645177248364272093977747839601125961863785073671961509749189348777945177811

n = p * q

e = 2
phi_n = (p - 1) * (q - 1)

while(e < phi_n):
    if gcd(e, phi_n) == 1:
        break
    else:
        e += 1


d = 1
for k in range(0, n):
    x = 1 + k * phi_n
    if(x % e == 0):
        d = x // e
        break
    

# print("K: ", k)
print("Public Key(Encryption): ", e)
print("Private Key(Decryption): ", d)
print("\n\n")



msg = 1807034343434343434
hash_object = hashlib.sha256(str(msg).encode())
hex_hash = hash_object.hexdigest()
hash_msg = int(hex_hash, 16)
print("The Message: ", msg)
# print("The Hash Message: ", hex_hash)
print("The Hash Message: ", hash_msg)
encrypted_digest = pow_big(hash_msg, d, n)
print("The Encrypted Digest: ", encrypted_digest)

#The sender now sends the original message with the encrypted has value
#The receiver now decrypts the encrypted value

print()
print()
expected_digest = pow_big(encrypted_digest, e, n)
print("The Expected(Decrypted) Digest: ", expected_digest)
actual_hash_object = hashlib.sha256(str(msg).encode())
actual_hex_hash = hash_object.hexdigest()
actual_digest = int(hex_hash, 16)
print("The Actual Digest: ", actual_digest)

print()
if(actual_digest == expected_digest):
    print("As the expected digest and actual digest are same, the signature is verified i.e. the message is okay.")
