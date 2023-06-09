/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:46:42 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/05/24 02:01:53 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pihlo.h"


In computing, a process and a thread are both fundamental concepts related to program execution,
 but they represent different units of execution and have distinct characteristics. 
 Here's a brief explanation of the difference between processes and threads:

Process: A process is an instance of a computer program that is being executed.
It is an independent entity with its own memory space, resources, and state. 
A process typically consists of a program's code, data, and associated system resources. 
Each process is isolated from other processes, meaning they cannot directly access each other's memory. 
Processes communicate with each other through inter-process communication mechanisms, such as pipes, 
sockets, or shared files. Processes are heavyweight entities that require a significant amount of system resources, including memory and time to create and manage.

Thread: A thread, on the other hand, is a unit of execution within a process.
 A process can have multiple threads, and each thread shares the same memory space and resources of the process it belongs to. 
 Threads are lighter-weight than processes and require fewer system resources. Threads within a process can execute concurrently, allowing multiple tasks to be performed simultaneously. 
 Since threads share the same memory, communication between threads within a process is relatively easier and faster compared to inter-process communication. 
 However, threads can also interfere with each other if they access shared data simultaneously without proper synchronization, leading to race conditions and other concurrency issues.

In summary, processes are independent programs that run in their own memory spaces and have their own resources, while threads are units of execution within a process that share the same memory space and resources. 
Processes are isolated from each other and communicate through inter-process communication, whereas threads within a process can communicate and share data more easily.