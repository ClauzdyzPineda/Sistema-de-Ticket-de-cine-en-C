please review actualizarUsuarios.

please review setId = it duplicates the id if a middle user is deleted. it needs to be fixed by fetching the last user and get the id of that user + 1