#!/bin/bash


git describe --tags --always --dirty 2>/dev/null || cat VERSION
