/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuuki <tyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:10:31 by tyuuki            #+#    #+#             */
/*   Updated: 2022/03/10 19:07:30 by tyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_take_fork(t_philo *philo)
{
	if(!philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		philo_message(philo, TAKE_F);
		pthread_mutex_lock(philo->right_fork);
		philo_message(philo, TAKE_F);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo_message(philo, TAKE_F);
		pthread_mutex_lock(philo->left_fork);
		philo_message(philo, TAKE_F);
	}
}

void	philo_putdown_fork(t_philo *philo)
{
	if(!philo->id % 2)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	philo_eat(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->inc_mutex);
	philo_message(philo, EAT);
	if(philo->data->eat_status == 1
		&& philo->data->must_eat - 1 != -1)
		philo->data->must_eat--;
	time = philo_time();
	philo->last_eat = philo_time();
	pthread_mutex_unlock(&philo->data->inc_mutex);
	while(philo_time() - time < philo->data->time_to_eat)
		usleep(100);
	philo_putdown_fork(philo);
}

void	philo_sleep(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->inc_mutex);
	philo_message(philo, SLEEP);
	time = philo_time();
	pthread_mutex_unlock(&philo->data->inc_mutex);
	while(philo_time() - time < philo->data->time_to_sleep)
		usleep(100);
	philo_message(philo, THINK);
}