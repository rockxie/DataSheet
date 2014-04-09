import binascii
from midstate import calculateMidstate

def make_input(block_header): 
    midstate = calculateMidstate(binascii.unhexlify(block_header)[:64])	
    data  = binascii.unhexlify(block_header)[65:76]    
    payload = midstate + data    
    print "Input: %s" % binascii.hexlify(payload)
        
make_input("000000020f60ba73a67140bb5e1272d809fe7b926739feb84137e1ee0000000300000000dd33336ac4fc668f930a09b2cd8317e9cec5b7c39648f787bbe02ee49544edde52908b9919070bfbde030000")

