/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClientSocket.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 11:53:18 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/06 13:50:17 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include "webserv.hpp"

class ClientSocket {
    private:
        int     _serverfd;
    public:
        ClientSocket(int socketfd);
        ~ClientSocket();
};

#endif