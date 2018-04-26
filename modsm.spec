Summary:  A utility for changing the ownership of shared memory.
Name: modsm
Version: 1.0
Release: 1
License: DWTFYL
Group: Utilities
Source: modsm-%{version}-%{release}.tar.gz
URL: https://github.com/duncster/modsm

%description
A utility for changing the ownership of shared memory.

%prep 
rm -rf %{buildroot}

%setup -q

%build
make

%install
install -d $RPM_BUILD_ROOT/usr
install -d $RPM_BUILD_ROOT/usr/local
install -d $RPM_BUILD_ROOT/usr/local/bin
install modsm $RPM_BUILD_ROOT/usr/local/bin

%files
%attr(755, root, root) /usr/local/bin/modsm

%changelog
* Thu Apr 26 2018 dunch <duncster@gmail.com>
- added .spec file
