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
# echo < run.sh < mola < test.c > kait > hello > fin1 > fin2
# echo yes < run.sh < test.c > kait
# echo yes < run.sh < test.c >> kait >> mola
# echo hello\how\are\you doing
# echo $PATH\hello
# echo yes \< run.sh
# echo \< run.sh
# echo \$PATH
#echo echo \"hello\"
# echo echo echo \'hello kd c lbc     jbh\'
# echo '$PATH' vs echo \'$PATH\'
# echo hello \' yes
# echo hello how\are\"you     doing\"
# echo hello how\are\'you     doing\'
# echo \no '\hello'
# echo \no "\ hello "
# echo hello \ $PATH  yes


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
export "labhairi=mouaad"; env >> export_origin.txt ; sed -i '.bak' 's/_\=.*//g' export_origin.txt ; sed -i '.bak' '/^$/d' export_origin.txt
