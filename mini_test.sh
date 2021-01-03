#                   BUILT-IN ECHO
echo  "###### ECHO ######" >> echo_mini.txt
./minishell "echo    hello    world"    >> echo_mini.txt
./minishell "echo hello world" >> echo_mini.txt
./minishell "echo '\$PATH' " >> echo_mini.txt
./minishell "echo \"hello 'world'\"" >> echo_mini.txt
./minishell "echo hello \$" >> echo_mini.txt
./minishell  "echo 'hello \"world\" '" >> echo_mini.txt
./minishell  "echo this \"is \"a tes't'" >> echo_mini.txt
./minishell "echo hello \"my\"friend" >> echo_mini.txt
./minishell "echo I 'like'\$PATH" >> echo_mini.txt
./minishell "echo mol\"abh\" 'ai'ri" >> echo_mini.txt
./minishell "echo \"hello \$mouad\"" >> echo_mini.txt
./minishell "echo ..." >> echo_mini.txt

#               BUILT_IN PWD
echo  "###### PWD ######" >> pwd_mini.txt
./minishell "pwd" >> pwd_mini.txt
./minishell "pwd pwd " >> pwd_mini.txt
./minishell "pwd pwd pwd pwd pwd pwd" >> pwd_mini.txt
./minishell "pwd pwd pwd pWd pwd pwd" >> pwd_mini.txt
./minishell "Pwd pwd pwd pwd pwd pwd" >> pwd_mini.txt
./minishell "pwd pwd pwd pwd pwd pwD" >> pwd_mini.txt
./minishell "PWD" >> pwd_mini.txt
./minishell "PWD pwd" >> pwd_mini.txt

#             BUILT_IN ENV
echo  "###### ENV #######" >> env_mini.txt
./minishell " env " >> env_mini.txt ; sed -i '.bak' 's/_\=.*//g' env_mini.txt ; sed -i '.bak' '/^$/d' env_mini.txt
./minishell "env env env en" >> env_mini.txt ; sed -i '.bak' 's/_\=.*//g' env_mini.txt ; sed -i '.bak' '/^$/d' env_mini.txt
./minishell "ENV" >> env_mini.txt ; sed -i '.bak' 's/_\=.*//g' env_mini.txt ; sed -i '.bak' '/^$/d' env_mini.txt
./minishell "Env" >> env_mini.txt ; sed -i '.bak' 's/_\=.*//g' env_mini.txt ; sed -i '.bak' '/^$/d' env_mini.txt
./minishell "eNv" >> env_mini.txt ; sed -i '.bak' 's/_\=.*//g' env_mini.txt ; sed -i '.bak' '/^$/d' env_mini.txt
./minishell "enV" >> env_mini.txt ; sed -i '.bak' 's/_\=.*//g' env_mini.txt ; sed -i '.bak' '/^$/d' env_mini.txt

#               BUILT_IN EXPORT
echo  "####### EXPORT #######" >> export.txt
./minishell "export \"casa=negra\"; env" >> export.txt ; sed -i '.bak' 's/_\=.*//g' export.txt ; sed -i '.bak' '/^$/d' export.txt
./minishell "export \"labhairi=mouaad\"; env" >> export.txt ; sed -i '.bak' 's/_\=.*//g' export.txt ; sed -i '.bak' '/^$/d' export.txt
#./minishell "export casa=mouaad ; env" >> export_mini.txt ; sed -i '.bak' 's/_\=.*//g' export_mini.txt ; sed -i '.bak' '/^$/d' export_mini.txt
#./minishell "export 'labhairi=negra'; env" >> export_mini.txt ; sed -i '.bak' 's/_\=.*//g' export_mini.txt ; sed -i '.bak' '/^$/d' export_mini.txt
#./minishell "export \"labhairi =mouaad\"; env" >> export_mini.txt ; sed -i '.bak' 's/_\=.*//g' export_mini.txt ; sed -i '.bak' '/^$/d' export_mini.txt
#./minishell "export \"lab= mouaad\"; env" >> export_mini.txt ; sed -i '.bak' 's/_\=.*//g' export_mini.txt ; sed -i '.bak' '/^$/d' export_mini.txt
sort -o export_mini.txt export.txt