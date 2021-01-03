#         BUILT_IN ECHO

echo  "###### ECHO ######" >> echo_origin.txt
echo    hello    world    >> echo_origin.txt
echo hello world >> echo_origin.txt
echo '$PATH' >> echo_origin.txt
echo "hello 'world'" >> echo_origin.txt
echo hello $ >> echo_origin.txt
echo 'hello "world" ' >> echo_origin.txt
echo this "is "a tes't' >> echo_origin.txt
echo hello "my"friend >> echo_origin.txt
echo I 'like'$PATH >> echo_origin.txt
echo mol"abh" 'ai'ri >> echo_origin.txt
echo "hello $mouad" >> echo_origin.txt
echo ... >> echo_origin.txt

#               BUILT_IN PWD
echo  "###### PWD ######" >> pwd_origin.txt
pwd  >> pwd_origin.txt 2>&1
pwd pwd  >> pwd_origin.txt 2>&1
pwd pwd pwd pwd pwd pwd  >> pwd_origin.txt 2>&1
pwd pwd pwd pWd pwd pwd  >> pwd_origin.txt 2>&1
Pwd pwd pwd pwd pwd pwd  >> pwd_origin.txt 2>&1
pwd pwd pwd pwd pwd pwD  >> pwd_origin.txt 2>&1
PWD >> pwd_origin.txt 2>&1
PWD pwd  >> pwd_origin.txt 2>&1

#               BUILT_IN ENV
echo  "###### ENV #######" >> env_origin.txt
env  >> env_origin.txt 2>&1 ; sed -i '.bak' 's/_\=.*//g' env_origin.txt ; sed -i '.bak' '/^$/d' env_origin.txt
env env env  >> env_origin.txt 2>&1 ; sed -i '.bak' 's/_\=.*//g' env_origin.txt ; sed -i '.bak' '/^$/d' env_origin.txt
ENV  >> env_origin.txt 2>&1 ; sed -i '.bak' 's/_\=.*//g' env_origin.txt ; sed -i '.bak' '/^$/d' env_origin.txt
Env  >> env_origin.txt 2>&1 ; sed -i '.bak' 's/_\=.*//g' env_origin.txt ; sed -i '.bak' '/^$/d' env_origin.txt
eNv  >> env_origin.txt 2>&1 ; sed -i '.bak' 's/_\=.*//g' env_origin.txt ; sed -i '.bak' '/^$/d' env_origin.txt
enV  >> env_origin.txt 2>&1 ; sed -i '.bak' 's/_\=.*//g' env_origin.txt ; sed -i '.bak' '/^$/d' env_origin.txt

#               BUILT_IN EXPORT
echo  "####### EXPORT #######" >> export_.txt
export "casa=negra"; env >> export_.txt ; sed -i '.bak' 's/_\=.*//g' export_.txt ; sed -i '.bak' '/^$/d' export_.txt
export "labhairi=mouaad"; env >> export_.txt ; sed -i '.bak' 's/_\=.*//g' export_.txt ; sed -i '.bak' '/^$/d' export_.txt
#export casa=mouaad ; env >> export_origin.txt ; sed -i '.bak' 's/_\=.*//g' export_origin.txt ; sed -i '.bak' '/^$/d' export_origin.txt
#export 'labhairi=negra'; env >> export_origin.txt ; sed -i '.bak' 's/_\=.*//g' export_origin.txt ; sed -i '.bak' '/^$/d' export_origin.txt
#export "labhairi =mouaad"; env >> export_origin.txt ; sed -i '.bak' 's/_\=.*//g' export_origin.txt ; sed -i '.bak' '/^$/d' export_origin.txt
#export "lab= mouaad"; env >> export_origin.txt ; sed -i '.bak' 's/_\=.*//g' export_origin.txt ; sed -i '.bak' '/^$/d' export_origin.txt
sort -o export_origin.txt export_.txt