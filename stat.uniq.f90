!/*
! * Filename   : stat.f90
! *
! * Created    : 17.05.2012
! *
! * Modified   : mar 17 may 14:00:26 2016
! *
! * Author     : 
! *
! * Purpose    :  
! *
! */

module parameters
    implicit none
    real(8), save         :: dt, tfin
    real(8), parameter    :: pi = 4.0d0*datan(1.0d0)
    integer, save         :: nstep, ncols
    integer               :: i, j, k
    character(len=7),save :: FileName
end module parameters

character(10) function timestamp()
    character(10) :: time
    call date_and_time(TIME=time)
    timestamp = time
end function

subroutine blog(fp,message)
    use parameters
    character*(*)    :: message
    character(len=7) :: fp
    interface
        function timestamp()
            character(10) :: timestamp
        end function
    end interface
    open(60,file=fp//'.log',position='append',action='write')
        write(60,*) '[ '//timestamp()//' ] '//trim(message)
    close(60)
end subroutine

subroutine correlation(node,x,y,acf)
    use parameters
    real(8), dimension(1:nstep),     intent(in)  :: x, y
    real(8), dimension(1:nstep/10),  intent(out) :: acf
    integer                                      :: ac_tmax, node
    real(8)                                      :: ac_tmp, xmean, ymean
    integer                                      :: step,col

    xmean = 0.0
    ymean = 0.0
    do step=0,nstep
        xmean = xmean + x(step)
        ymean = ymean + y(step)
    end do
    xmean = xmean / nstep
    ymean = ymean / nstep

    do step=1, nstep/10
        ac_tmax = nstep - step
        ac_tmp = 0.0
        do col = 1, ac_tmax
            ac_tmp = ac_tmp + x(col) * y(col+step)
        end do
        acf(step) = ac_tmp/float(ac_tmax) - xmean*ymean
    end do
end subroutine correlation

subroutine ReadFile(filept,src)
    use parameters
    character(len=7) :: filept
    real(8), dimension(1:nstep,1:ncols), intent(out) :: src

    open(10,file=filept)
    do i=1,nstep
        read(10,*) (src(i,j),j=1,ncols)
    end do
    close(10)
end subroutine ReadFile

program stat
    use parameters
    real(8), dimension(:,:), allocatable :: src
    real(8), dimension(:,:), allocatable :: cf, acf
    integer                              :: bet, l
    character(len=20)                    :: ll,rr

    nstep = 3000
    ncols = 64 

    allocate(src(1:nstep,1:ncols))
    allocate( cf(1:nstep/10,1:ncols/2))
    allocate(acf(1:nstep/10,1:ncols*ncols))
    
    call get_command_argument(1,FileName)
    call blog(FileName,'Starting...')
    call ReadFile(FileName, src)
    call blog(FileName,'File read...')

!     open(20,file="output.dat")
!     do i=1,nstep
!         write (20,*) (src(i,j),j=1,ncols)
!     end do
!     close(20)
! 
!     print *, 'Checking completed...'

    acf = 0

    !$OMP PARALLEL SHARED(src,acf,l,ll,ncols) PRIVATE(k)
    !$OMP DO SCHEDULE(GUIDED)
    do l=0,ncols-1
       write(ll,*) l+1
       ll=adjustl(ll)
       call blog(FileName,'Calling correlations for node '//trim(ll))
       do k=1,ncols
           call correlation(l+1,src(:,l+1),src(:,k),acf(:,l*ncols+k))
       end do
    end do
    !$OMP END DO
    !$OMP END PARALLEL
    
    acf = acf / ncols

    call blog(FileName,'Correlations computed')

    open(30,file=FileName//"-cf.dat")
    do i=1,nstep/10
        write(30,*) (acf(i,j),j=1,ncols*ncols)
    end do
    close(30)

    call blog(FileName,'Exiting now')

end program stat

