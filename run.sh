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

#!/bin/sh

sh mini_test.sh

sh echo_origin.sh

cmp   echo_origin.txt echo_mini.txt
#diff  -B -c  -s   mini_file.txt origin_file.txt

rm echo_origin.txt echo_mini.txt
rm pwd_origin.txt pwd_mini.txt
rm env_origin.txt env_mini.txt
