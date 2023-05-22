# CMake generated Testfile for 
# Source directory: /home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins
# Build directory: /home/lucads/irobot_ws/build/irobot_create_ignition_plugins
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cppcheck "/usr/bin/python3.8" "-u" "/home/lucads/ros2_humble/install/ament_cmake_test/share/ament_cmake_test/cmake/run_test.py" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/test_results/irobot_create_ignition_plugins/cppcheck.xunit.xml" "--package-name" "irobot_create_ignition_plugins" "--output-file" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/ament_cppcheck/cppcheck.txt" "--command" "/home/lucads/ros2_humble/install/ament_cppcheck/bin/ament_cppcheck" "--xunit-file" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/test_results/irobot_create_ignition_plugins/cppcheck.xunit.xml")
set_tests_properties(cppcheck PROPERTIES  LABELS "cppcheck;linter" TIMEOUT "300" WORKING_DIRECTORY "/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins" _BACKTRACE_TRIPLES "/home/lucads/ros2_humble/install/ament_cmake_test/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/home/lucads/ros2_humble/install/ament_cmake_cppcheck/share/ament_cmake_cppcheck/cmake/ament_cppcheck.cmake;66;ament_add_test;/home/lucads/ros2_humble/install/ament_cmake_cppcheck/share/ament_cmake_cppcheck/cmake/ament_cmake_cppcheck_lint_hook.cmake;83;ament_cppcheck;/home/lucads/ros2_humble/install/ament_cmake_cppcheck/share/ament_cmake_cppcheck/cmake/ament_cmake_cppcheck_lint_hook.cmake;0;;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/home/lucads/ros2_humble/install/ament_lint_auto/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;21;ament_execute_extensions;/home/lucads/ros2_humble/install/ament_lint_auto/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;0;;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_package.cmake;66;ament_execute_extensions;/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins/CMakeLists.txt;31;ament_package;/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins/CMakeLists.txt;0;")
add_test(cpplint "/usr/bin/python3.8" "-u" "/home/lucads/ros2_humble/install/ament_cmake_test/share/ament_cmake_test/cmake/run_test.py" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/test_results/irobot_create_ignition_plugins/cpplint.xunit.xml" "--package-name" "irobot_create_ignition_plugins" "--output-file" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/ament_cpplint/cpplint.txt" "--command" "/home/lucads/ros2_humble/install/ament_cpplint/bin/ament_cpplint" "--xunit-file" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/test_results/irobot_create_ignition_plugins/cpplint.xunit.xml")
set_tests_properties(cpplint PROPERTIES  LABELS "cpplint;linter" TIMEOUT "120" WORKING_DIRECTORY "/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins" _BACKTRACE_TRIPLES "/home/lucads/ros2_humble/install/ament_cmake_test/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/home/lucads/ros2_humble/install/ament_cmake_cpplint/share/ament_cmake_cpplint/cmake/ament_cpplint.cmake;68;ament_add_test;/home/lucads/ros2_humble/install/ament_cmake_cpplint/share/ament_cmake_cpplint/cmake/ament_cmake_cpplint_lint_hook.cmake;35;ament_cpplint;/home/lucads/ros2_humble/install/ament_cmake_cpplint/share/ament_cmake_cpplint/cmake/ament_cmake_cpplint_lint_hook.cmake;0;;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/home/lucads/ros2_humble/install/ament_lint_auto/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;21;ament_execute_extensions;/home/lucads/ros2_humble/install/ament_lint_auto/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;0;;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_package.cmake;66;ament_execute_extensions;/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins/CMakeLists.txt;31;ament_package;/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins/CMakeLists.txt;0;")
add_test(lint_cmake "/usr/bin/python3.8" "-u" "/home/lucads/ros2_humble/install/ament_cmake_test/share/ament_cmake_test/cmake/run_test.py" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/test_results/irobot_create_ignition_plugins/lint_cmake.xunit.xml" "--package-name" "irobot_create_ignition_plugins" "--output-file" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/ament_lint_cmake/lint_cmake.txt" "--command" "/home/lucads/ros2_humble/install/ament_lint_cmake/bin/ament_lint_cmake" "--xunit-file" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/test_results/irobot_create_ignition_plugins/lint_cmake.xunit.xml")
set_tests_properties(lint_cmake PROPERTIES  LABELS "lint_cmake;linter" TIMEOUT "60" WORKING_DIRECTORY "/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins" _BACKTRACE_TRIPLES "/home/lucads/ros2_humble/install/ament_cmake_test/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/home/lucads/ros2_humble/install/ament_cmake_lint_cmake/share/ament_cmake_lint_cmake/cmake/ament_lint_cmake.cmake;47;ament_add_test;/home/lucads/ros2_humble/install/ament_cmake_lint_cmake/share/ament_cmake_lint_cmake/cmake/ament_cmake_lint_cmake_lint_hook.cmake;21;ament_lint_cmake;/home/lucads/ros2_humble/install/ament_cmake_lint_cmake/share/ament_cmake_lint_cmake/cmake/ament_cmake_lint_cmake_lint_hook.cmake;0;;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/home/lucads/ros2_humble/install/ament_lint_auto/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;21;ament_execute_extensions;/home/lucads/ros2_humble/install/ament_lint_auto/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;0;;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_package.cmake;66;ament_execute_extensions;/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins/CMakeLists.txt;31;ament_package;/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins/CMakeLists.txt;0;")
add_test(xmllint "/usr/bin/python3.8" "-u" "/home/lucads/ros2_humble/install/ament_cmake_test/share/ament_cmake_test/cmake/run_test.py" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/test_results/irobot_create_ignition_plugins/xmllint.xunit.xml" "--package-name" "irobot_create_ignition_plugins" "--output-file" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/ament_xmllint/xmllint.txt" "--command" "/home/lucads/ros2_humble/install/ament_xmllint/bin/ament_xmllint" "--xunit-file" "/home/lucads/irobot_ws/build/irobot_create_ignition_plugins/test_results/irobot_create_ignition_plugins/xmllint.xunit.xml")
set_tests_properties(xmllint PROPERTIES  LABELS "xmllint;linter" TIMEOUT "60" WORKING_DIRECTORY "/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins" _BACKTRACE_TRIPLES "/home/lucads/ros2_humble/install/ament_cmake_test/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/home/lucads/ros2_humble/install/ament_cmake_xmllint/share/ament_cmake_xmllint/cmake/ament_xmllint.cmake;50;ament_add_test;/home/lucads/ros2_humble/install/ament_cmake_xmllint/share/ament_cmake_xmllint/cmake/ament_cmake_xmllint_lint_hook.cmake;18;ament_xmllint;/home/lucads/ros2_humble/install/ament_cmake_xmllint/share/ament_cmake_xmllint/cmake/ament_cmake_xmllint_lint_hook.cmake;0;;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/home/lucads/ros2_humble/install/ament_lint_auto/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;21;ament_execute_extensions;/home/lucads/ros2_humble/install/ament_lint_auto/share/ament_lint_auto/cmake/ament_lint_auto_package_hook.cmake;0;;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_execute_extensions.cmake;48;include;/home/lucads/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_package.cmake;66;ament_execute_extensions;/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins/CMakeLists.txt;31;ament_package;/home/lucads/irobot_ws/src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins/CMakeLists.txt;0;")
subdirs("Create3Hmi")
