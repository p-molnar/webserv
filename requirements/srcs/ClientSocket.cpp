/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClientSocket.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 13:43:56 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/06 13:46:30 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(int socketfd) : _serverfd(socketfd)
{
}

ClientSocket::~ClientSocket()
{
    close(this->_serverfd);
}