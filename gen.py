m="""
    #####          
    #   #          
    #$  #          
  ###  $##         
  #  $ $ #         
### # ## #   ######
#   # ## #####  ..#
# $  $          ..#
##### ### #@##  ..#
    #     #########
    #######        
"""
m=m.replace(' ','0').replace('.','0').replace('#', '1').replace('$', '2').replace('*', '2').replace('@', '3').replace('\n', '').replace('\r', '')
print('{'+','.join(list(m))+'};')
print(len(m))