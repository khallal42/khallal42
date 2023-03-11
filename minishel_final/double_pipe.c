if	(l_lstsize(data) == 2)
{
	//char	*s1[];
	pipe(fdp);
	i = fork();
	if (i == 0)
	{
		while (data->infile[j])
		{
			fd = open(data->infile[j], O_RDONLY);
			j++;
			if (fd < 0)
				(perror("here___"), exit(1));
		}
		if (fd != -1)
			dup2(fd, 0); //ghadi ywali lfille.tx howa input
		close(fdp[0]);
		j = 0;
		while (data->outfile[j])
		{
			fd1 = open(data->outfile[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
			j++;
			if (fd < 0)
				(perror(""), exit(1));
		}
		if (fd1 != -1)
			dup2(fd1, 1);
		else
			dup2(fdp[1], 1);
		// ghadi nhat l output dyal l command f pipe
		k = split_path(env);
		//l = ft_split(av[1], ' ');
		cmd = ft_access(k, data->full_cmd[0]);
		//s1[] = {l, NULL};
		if (execve(cmd, data->full_cmd, NULL) == -1)
			(perror("bash : command not found\n"), exit(1));
	}
	else
	{
		data = data->next;
		pid = fork();
		//printf("-----%d\n", j);
		if (pid == 0)
		{
			while (data->outfile[j])
			{
				fd1 = open(data->outfile[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
				j++;
				if (fd1 < 0)
					exit(1);
			}
			if (fd1 > 0)
				dup2(fd1, 1); // uotput nhato f lfille fd1
			close(fdp[1]);
			j = 0;
			//printf("\n------%s\n--------\n", data->infile[j]);
			while (data->infile[j])
			{
				fd = open(data->infile[j], O_RDONLY);
				j++;
				if (fd < 0)
					(perror(""), exit(1));
			}
			if (fd != -1)
				dup2(fd, 0);
			else
				dup2(fdp[0], 0); // n9ra dak chi mn l pipe fdp[0]
			k = split_path(env);
			// l = ft_split(av[2], ' ');
			cmd = ft_access(k, data->full_cmd[0]);
			if (execve(cmd, data->full_cmd, NULL) == -1)
				(perror("kkk : command not found\n"), exit(1));
		}
	}
	close(fdp[1]);
	close(fdp[0]);
	while (wait(NULL) != -1)
		;
	//waitpid(pid, NULL, 0);
}
else if	(l_lstsize(data) >= 3)
	multiple(data, env);