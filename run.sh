# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molabhai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 14:03:50 by molabhai          #+#    #+#              #
#    Updated: 2020/12/22 19:45:33 by molabhai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

sh mini_test.sh

sh echo_origin.sh

diff  -s -a -c mini_file.txt origin_file.txt

rm mini_file.txt origin_file.txt
