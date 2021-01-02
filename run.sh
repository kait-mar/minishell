# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molabhai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 14:03:50 by molabhai          #+#    #+#              #
#    Updated: 2020/12/23 10:46:27 by molabhai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

sh mini_test.sh
sh echo_origin.sh

diff  -B -c  -s   echo_origin.txt echo_mini.txt
diff  -B -c  -s   pwd_origin.txt pwd_mini.txt
diff  -B -c  -s   env_origin.txt env_mini.txt
diff  -B -c  -s   export_origin.txt export_mini.txt

rm echo_origin.txt echo_mini.txt
rm pwd_origin.txt pwd_mini.txt
rm env_origin.txt env_mini.txt
#rm export_origin.txt export_mini.txt
rm *.bak