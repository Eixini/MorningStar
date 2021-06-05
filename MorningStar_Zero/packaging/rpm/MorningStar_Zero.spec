Name: MorningStar_Zero
Version: 0.1.1
Release: 1%{?dist}

%global shortname MorningStar

License: LGPLv2+
Summary: MorningStar Zero application

URL: https://github.com/Eixini/MorningStar
Source0: %{url}/archive/v%{version}/%{shortname}-%{version}.tar.gz 

BuildRequires: cmake
BuildRequires: gcc
BuildRequires: gcc-c++
BuildRequires: ninja-build

BuildRequires: cmake(Qt5LinguistTools)
BuildRequires: cmake(Qt5Multimedia)
BuildRequires: cmake(Qt5X11Extras)
BuildRequires: cmake(Qt5Network)
BuildRequires: cmake(Qt5Core)
BuildRequires: cmake(Qt5DBus)
BuildRequires: cmake(Qt5Gui)
  
%description
Modular project with the diverse functionality like requesting time from the
Internet, creating and editing notes, and another.
 
%prep
%autosetup -n %{shortname}-%{version}
 
%build
%cmake
%cmake_build
 
%install
%cmake_install
 
%check
 
%files
%{_bindir}/%{name}
%doc README.md

%changelog
* Sat Mar 20 2021 Eixini eixi16@gmail.com - 0.1.1-1
- First Release

