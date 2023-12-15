/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PollManager.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 14:35:38 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/15 14:38:04 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

class PollManager {
    private:
        std::vector<struct pollfd> fds;

    public:

};