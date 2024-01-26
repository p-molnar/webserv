#include "RequestProcessor.hpp"

void RequestProcessor::uploadFiles(const HttpRequest &request)
{
	FormData form_data = request.getFormDataObj();
	for (t_form_data fdata : form_data.getFormData())
	{
		std::string filename = fdata.overhead.content_disposition.at("filename");
		// from config file
		std::string path = "srv/uploads/" + filename;

		int fd;
		if ((fd = open(path.c_str(), O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH)) < 0)
			throw std::runtime_error("Error while opening " + filename + ": " + STRERR);

		std::size_t size = fdata.payload.length();
		write(fd, fdata.payload.c_str(), size);
		close(fd);
	}
}
