# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molabhai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 14:03:50 by molabhai          #+#    #+#              #
#    Updated: 2020/12/22 14:50:30 by molabhai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

sh mini_test.sh

sh echo_origin.sh

diff  -B -c  -s   mini_file.txt origin_file.txt

rm mini_file.txt origin_file.txt
