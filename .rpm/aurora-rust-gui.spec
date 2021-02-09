%define __spec_install_post %{nil}
%define __os_install_post %{_dbpath}/brp-compress
%define debug_package %{nil}

Name: aurora-rust-gui
Summary: Rust GUI example for Aurora OS
Version: @@VERSION@@
Release: @@RELEASE@@%{?dist}
License: MIT
Group: Qt/Qt
Source0: %{name}-%{version}.tar.gz
Source1: %{name}.desktop
Source2: icons
Source3: qml
Requires: sailfishsilica-qt5 >= 0.10.9

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root

%description
%{summary}

%prep
%setup -q

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}
cp -a * %{buildroot}
mkdir -p %{buildroot}%{_datadir}/applications
cp -a %{SOURCE1} %{buildroot}%{_datadir}/applications
mkdir -p %{buildroot}%{_datadir}/icons/hicolor/86x86/apps
mkdir -p %{buildroot}%{_datadir}/icons/hicolor/108x108/apps
mkdir -p %{buildroot}%{_datadir}/icons/hicolor/128x128/apps
mkdir -p %{buildroot}%{_datadir}/icons/hicolor/172x172/apps
cp -a %{SOURCE2}/86x86/%{name}.png %{buildroot}%{_datadir}/icons/hicolor/86x86/apps
cp -a %{SOURCE2}/108x108/%{name}.png %{buildroot}%{_datadir}/icons/hicolor/108x108/apps
cp -a %{SOURCE2}/128x128/%{name}.png %{buildroot}%{_datadir}/icons/hicolor/128x128/apps
cp -a %{SOURCE2}/172x172/%{name}.png %{buildroot}%{_datadir}/icons/hicolor/172x172/apps
mkdir -p %{buildroot}%{_datadir}/%{name}
cp -ra %{SOURCE3} %{buildroot}%{_datadir}/%{name}/qml

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_bindir}/*
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
%{_datadir}/%{name}/qml
