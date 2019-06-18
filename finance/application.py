import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol, quantity_raw = request.form.values()

        # Ensure any symbol was submitted
        if not symbol:
            return apology("must provide symbol", 403)

        # Ensure integer number was submitted
        try:
            quantity_converted = int(quantity_raw)
        except:
            return apology("must provide whole numbers for shares", 403)

        # Ensure any positive number of shares was submitted
        if quantity_converted < 1:
            return apology("must provide at least one share", 403)

        # Look up symbol on IEX
        quote = lookup(symbol)

        # Ensure symbol exists
        if not quote:
            return apology("symbol not found", 404)

        # Ensure float number was returned for price by api
        name, price_raw, symbol = quote.values()
        try:
            price_converted = float(price_raw)
        except:
            return apology("there was a problem with finding your symbol", 404)

        # Round price to 4 digits and calculate total value of purchase
        price_rounded = round(price_converted, 4)
        total = price_rounded * quantity_converted

        # Query database for users's cash
        user_id = session["user_id"]
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)

        # Check if user has enough cash for purchase
        cash = rows[0]["cash"]
        cash_remaining = cash - total
        if not (cash_remaining >= 0):
            return apology("not enough cash for purchase", 403)

        # Insert transaction into database
        db.execute(
            "INSERT INTO transactions (action, symbol, quantity, price, idUser) VALUES ('buy', :symbol, :quantity, :price, :idUser)",
            symbol=symbol,
            quantity=quantity_converted,
            price=price_rounded,
            idUser=user_id,
        )

        # Update user's cash
        db.execute(
            "Update users SET cash = :cash WHERE id = :id",
            cash=cash_remaining,
            id=user_id,
        )

        # Create success notification
        flash(
            f"Successfully purchased {quantity_converted} {symbol} shares for {price_rounded} per share."
        )

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html.j2")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    return jsonify("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = :username",
            username=request.form.get("username"),
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 401)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Create success notification
        flash("Successfully logged in.")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html.j2")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Ensure any symbol was submitted
        if not symbol:
            return apology("must provide symbol", 403)

        # Look up symbol on IEX
        quote = lookup(symbol)

        # Ensure symbol exists
        if not quote:
            return apology("symbol not found", 404)

        # Render diplay template with quote
        name, price, symbol = quote.values()
        return render_template(
            "display.html.j2", name=name, price=usd(price), symbol=symbol
        )

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html.j2")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username, password, password_confirm = request.form.values()

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 403)

        # Ensure password confirmation was submitted
        elif not password_confirm:
            return apology("must provide password confirmation", 403)

        # Ensure password and password confirmation match
        elif not password == password_confirm:
            return apology("password and password confirmation must match", 403)

        # Generate password hash
        hash = generate_password_hash(password)

        # Insert user to database
        user_id = db.execute(
            "INSERT INTO users (username, hash) VALUES (:username, :hash)",
            username=username,
            hash=hash,
        )

        # Check if username already exists
        if not user_id:
            return apology("username already taken", 403)

        # Skip login and directly remember registered user
        session["user_id"] = user_id

        # Create success notification
        flash("Successfully registered.")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html.j2")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
