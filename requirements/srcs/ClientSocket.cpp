/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClientSocket.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 13:43:56 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 08:53:32 by dickklouwer   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(int socketfd) : _serverfd(socketfd)
{
}

ClientSocket::~ClientSocket()
{
    ::close(this->_serverfd);
}